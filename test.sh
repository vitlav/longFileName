gcc -o main  main.c

sudo apt install btrfs-progs

truncate --size=1G FAT.txt
sudo mkfs.fat FAT.txt
mkdir fat
sudo mount FAT.txt fat

truncate --size=1G exFAT.txt
sudo mkfs.exfat exFAT.txt
mkdir exFAT
sudo mount exFAT.txt exFAT

truncate --size=1G ext4.txt
sudo mkfs.ext4 ext4.txt
mkdir ext4
sudo mount ext4.txt ext4

truncate --size=1G btrfs.txt
sudo mkfs.btrfs btrfs.txt
mkdir btrfs
sudo mount btrfs.txt btrfs

truncate --size=1G ntfs.txt
blockDevice=`sudo losetup -f`
sudo losetup $blockDevice ntfs.txt
sudo mkntfs $blockDevice
mkdir ntfs
sudo mount $blockDevice ntfs

echo -e "\nFAT file system check:"
./main fat
sudo umount fat
rmdir fat
rm FAT.txt

echo -e "\nexFAT file system check:"
./main exFAT
sudo umount exFAT
rmdir exFAT
rm exFAT.txt

echo -e "\next4 file system check:"
./main ext4
sudo umount ext4
rmdir ext4
rm ext4.txt

echo -e "\nbtrfs file system check:"
./main btrfs
sudo umount btrfs
rmdir btrfs
rm btrfs.txt

echo -e "\nntfs file system check:"
./main ntfs
sudo umount ntfs
sudo losetup -d $blockDevice
rmdir ntfs
rm ntfs.txt
