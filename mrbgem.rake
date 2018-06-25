MRuby::Gem::Specification.new('mruby-ftdi') do |spec|
  spec.license = 'BSD'
  spec.authors = 'Hiroki Mori'
  spec.linker.libraries << ['ftdi']
  spec.cc.include_paths << "/usr/local/include/"
  if(ENV['ZWORLDDESTDIR'] != nil)
    spec.linker.library_paths << (ENV['ZWORLDDESTDIR'] + '/usr/local/lib')
  else
    spec.linker.library_paths << "/usr/local/lib"
  end

end
