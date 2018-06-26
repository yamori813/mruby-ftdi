/*
** mrb_ftdi.c - Ftdi class
**
** Copyright (c) Hiroki Mori 2018
**
** See Copyright Notice in LICENSE
*/

#include <ftdi.h>

#include "mruby.h"
#include "mruby/data.h"
#include "mruby/array.h"
#include "mrb_ftdi.h"

#define DONE mrb_gc_arena_restore(mrb, 0);

typedef struct {
  char *str;
  int len;
  struct ftdi_context ftdic;
} mrb_ftdi_data;

static const struct mrb_data_type mrb_ftdi_data_type = {
  "mrb_ftdi_data", mrb_free,
};

static mrb_value mrb_ftdi_init(mrb_state *mrb, mrb_value self)
{
  mrb_ftdi_data *data;
  mrb_int pid, mask;

  data = (mrb_ftdi_data *)DATA_PTR(self);
  if (data) {
    mrb_free(mrb, data);
  }
  DATA_TYPE(self) = &mrb_ftdi_data_type;
  DATA_PTR(self) = NULL;

  mrb_get_args(mrb, "ii", &pid, &mask);
  data = (mrb_ftdi_data *)mrb_malloc(mrb, sizeof(mrb_ftdi_data));
  ftdi_init(&data->ftdic);
  ftdi_usb_open(&data->ftdic, 0x0403, pid);
  ftdi_set_bitmode(&data->ftdic, mask, BITMODE_BITBANG);
  DATA_PTR(self) = data;

  return self;
}

static mrb_value mrb_ftdi_baudrate(mrb_state *mrb, mrb_value self)
{
  mrb_ftdi_data *data = DATA_PTR(self);
  mrb_int rate;
  mrb_get_args(mrb, "i", &rate);
  ftdi_set_baudrate(&data->ftdic, rate);
}

#define MAXBUF 1024

static mrb_value mrb_ftdi_write(mrb_state *mrb, mrb_value self)
{
  mrb_ftdi_data *data = DATA_PTR(self);
  int i, len;
  unsigned char buf[MAXBUF];
  mrb_value arr;

  mrb_get_args(mrb, "A", &arr);
  len = RARRAY_LEN( arr );

  if (len > MAXBUF)
    return mrb_nil_value();

  for (i = 0; i < len; ++i)
    buf[i] = mrb_fixnum( mrb_ary_ref( mrb, arr, i ) );

  ftdi_write_data(&data->ftdic, buf, len);
  return mrb_nil_value();
}

static mrb_value mrb_ftdi_close(mrb_state *mrb, mrb_value self)
{
  mrb_ftdi_data *data = DATA_PTR(self);

  ftdi_usb_close(&data->ftdic);
  ftdi_deinit(&data->ftdic);
}

void mrb_mruby_ftdi_gem_init(mrb_state *mrb)
{
  struct RClass *ftdi;
  ftdi = mrb_define_class(mrb, "Ftdi", mrb->object_class);
  mrb_define_method(mrb, ftdi, "initialize", mrb_ftdi_init, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, ftdi, "baudrate", mrb_ftdi_baudrate, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ftdi, "write", mrb_ftdi_write, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ftdi, "close", mrb_ftdi_close, MRB_ARGS_NONE());
  DONE;
}

void mrb_mruby_ftdi_gem_final(mrb_state *mrb)
{
}

