gcc -o main  main.c

truncate --size=1G FAT.txt
sudo mkfs.fat FAT.txt
mkdir fat
sudo mount FAT.txt fat
echo -e "\nFAT file system mounted successfully!"
echo "Let's check it..."
./main fat
sudo umount fat
rmdir fat
rm FAT.txt
echo ""

truncate --size=1G exFAT.txt
sudo mkfs.exfat exFAT.txt
mkdir exFAT
sudo mount exFAT.txt exFAT
echo -e "\nexFAT file system mounted successfully!"
echo "Let's check it..."
./main exFAT
sudo umount exFAT
rmdir exFAT
rm exFAT.txt
echo ""

truncate --size=1G ext4.txt
sudo mkfs.ext4 ext4.txt
mkdir ext4
sudo mount ext4.txt ext4
echo -e "\next4 file system mounted successfully!"
echo "Let's check it..."
./main ext4
sudo umount ext4
rmdir ext4
rm ext4.txt
echo ""
