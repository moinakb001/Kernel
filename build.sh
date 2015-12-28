mkdir ./build -p
mkdir ./artifacts -p
mkdir ./build/objfiles -p
mkdir ./build/isodir/boot/grub -p

i=1
for file in ./*
do
	echo "$file"
	if [ "${file##*.}" == "asm" ];
	then
		nasm -felf32 "$file" -o "./build/objfiles/${file%.*}$i.o"
	fi
	if [ "${file##*.}" == "cpp" ];
	then
		clang++ -target i686-elf -c "$file" -o "./build/objfiles/${file%.*}$i.o" -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
	fi
	i=i+1
done
i686-elf-gcc -T "linker.ld" -o "./artifacts/myos.bin" -ffreestanding -O2 -nostdlib ./build/objfiles/* -lgcc
cp ./artifacts/myos.bin ./build/isodir/boot/myos.bin
cp ./grub.cfg ./build/isodir/boot/grub/grub.cfg
grub-mkrescue -o artifacts/myos.iso ./build/isodir
rm -rf build
