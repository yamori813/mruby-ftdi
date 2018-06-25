# mruby-ftdi   [![Build Status](https://travis-ci.org/yamori813/mruby-ftdi.svg?branch=master)](https://travis-ci.org/yamori813/mruby-ftdi)
Ftdi class
## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :github => 'yamori813/mruby-ftdi'
end
```
## example
```ruby
t = Ftdi.new(0x6001, 0xff)
t.write([0x01])
```

## License
under the BSD License:
- see LICENSE file
