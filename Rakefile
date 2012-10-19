require 'rake'
require 'rake/clean'
require 'tmpdir'

CC      = 'gcc'
AR      = 'ar'
CFLAGS  = '-std=gnu99 -Iinclude -Ivendor/libuv/include -Ivendor/openssl/include -Ivendor/zlib'
LDFLAGS = '-lm -ldl -lpthread -lrt'

SOURCES      = FileList['sources/**/*.c']
OBJECTS      = SOURCES.ext('o')
DEPENDENCIES = FileList['vendor/libuv/libuv.a', 'vendor/openssl/libcrypto.a', 'vendor/openssl/libssl.a', 'vendor/zlib/libz.a']

CLEAN.include(OBJECTS)
CLOBBER.include('libtor.so', 'libtor-static.a', 'test/run', DEPENDENCIES)

task :default => :build

task :build, :mode do |t, args|
	mode = (args[:mode] || :debug).to_sym

	if mode == :debug
		CFLAGS << ' -O0 -g3'
	else
		CFLAGS << ' -Os -DNDEBUG'
	end

	Rake::Task['build:libtor'].invoke
end

namespace :build do
	task :libtor => ['libtor.so', 'libtor-static.a']

	task :libuv => 'submodules:libuv' do
		Dir.chdir 'vendor/libuv' do
			ENV['CFLAGS'] = '-fPIC'

			sh 'make'
		end
	end

	task :openssl => 'submodules:openssl' do
		Dir.chdir 'vendor/openssl' do
			sh './config -fPIC no-shared threads'
			sh 'make'
		end
	end

	task :zlib => 'submodules:zlib' do
		Dir.chdir 'vendor/zlib' do
			ENV['CFLAGS'] = '-O3 -fPIC'

			sh './configure --static'
			sh 'make'
		end
	end

	file 'libtor.so' => DEPENDENCIES + OBJECTS do
		sh "#{CC} #{CFLAGS} -fPIC #{OBJECTS} #{DEPENDENCIES} -shared -Wl,-soname,libtor -o libtor.so #{LDFLAGS}"
	end

	file 'libtor-static.a' => DEPENDENCIES + OBJECTS do
		Dir.mktmpdir {|path|
			DEPENDENCIES.each {|name|
				real = File.realpath(name)

				FileUtils.mkpath "#{path}/#{File.basename(name)}"
				FileUtils.chdir "#{path}/#{File.basename(name)}" do
					sh "#{AR} x #{real}"
				end
			}

			sh "#{AR} rcs libtor-static.a #{OBJECTS} #{path}/*/*.o"
		}
	end

	file 'vendor/libuv/libuv.a' do
		Rake::Task['build:libuv'].invoke
	end

	file 'vendor/openssl/libcrypto.a' do
		Rake::Task['build:openssl'].invoke
	end

	file 'vendor/openssl/libssl.a' do
		Rake::Task['build:openssl'].invoke
	end

	file 'vendor/zlib/libz.a' do
		Rake::Task['build:zlib'].invoke
	end
end

task :test => 'test:run'

namespace :test do
	files = FileList['test/*.c'].each

	task :build => 'test/run'

	task :run => 'test:build' do
		sh 'test/run'
	end

	files.each {|path|
		file path
	}

	file 'test/run' => ['libtor-static.a', *files] do
		sh "#{CC} -std=gnu99 -Iinclude -Ivendor/tinytest -o test/run test/run.c vendor/tinytest/tinytest.c -L. -ltor-static #{LDFLAGS}"
	end
end

namespace :submodules do
	task :fetch do
		sh 'git submodule init'
		sh 'git submodule update'
	end

	task :libuv => 'vendor/libuv/Makefile'

	task :openssl => 'vendor/openssl/config'

	task :zlib => 'vendor/zlib/configure'

	task :tinytest => 'vendor/tinytest/tinytest.c'

	file 'vendor/libuv/Makefile' do
		Rake::Task['submodules:fetch'].invoke
	end

	file 'vendor/openssl/config' do
		Rake::Task['submodules:fetch'].invoke
	end

	file 'vendor/zlib/configure' do
		Rake::Task['submodules:fetch'].invoke
	end

	file 'vendor/tinytest/tinytest.c' do
		Rake::Task['submodules:fetch'].invoke
	end
end

rule '.o' => '.c' do |t|
	sh "#{CC} #{CFLAGS} -fPIC -o #{t.name} -c #{t.source}"
end
