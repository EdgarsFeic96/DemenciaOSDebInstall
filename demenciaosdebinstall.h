#ifndef DEMENCIAOSDEBINSTALL_H_INCLUDED
#define DEMENCIAOSDEBINSTALL_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

int option; // Variable que guara la opcion elegida del inicio
string swapoption; // Opcion donde se guarda si quieres la swap o no
string disk; // Variable donde se almacena el disco de destino
string rootpart; // Variable de la partición raiz..
string efipart; // Variable donde se almacena la partición EFI
string swappart; // Variable donde se almacena la partición SWAP
string efioption; // Variable para especificar si es una instalación EFI o no.
string unsquashfs = "unsquashfs -f -d /media/target/ /usr/lib/live/mount/medium/live/filesystem.squashfs";
string createSwap = "mkswap " + swappart;
string EnableSwap = "swapon " + swappart;
string fdiskrun = "cfdisk " + disk;
string installGRUBLegacy = "grub-install --target=i386-pc --root-directory=/media/target/ " + disk;
string mountLegacyRoot = "mount -t ext4 " + rootpart + " /media/target";
string mkRootLegacy = "mkfs.ext4 " + rootpart;
string runMkdirTargetDir = "mkdir /media/target/";
string mkBootDir = "mkdir /media/target/boot/";
string mkEFIpart = "mkfs.vfat -F 32 " + disk=disk+"1";
string mountEFIpart = "mount " + efipart + " /media/target/boot";
string mkRootPart = "mkfs.ext4 " + rootpart;
string mountRoot = "mount " + rootpart + " /media/target";
bool usingSwap; // Variable para especificar si se usa la SWAP
bool isEFI; // Comprobar si la instalación es EFI y no.

void installgenfstab()
{
    system("apt install arch-install-scripts -y ");
}

bool startsWith(std::string primera_str, std::string str_objetivo)
{
    // std::string::find returns 0 if toMatch is found at starting
    if(primera_str.find(str_objetivo) == 0)
        return true;
    else
        return false;
}

void mountProc()
{
    system("mount --bind /proc/ /media/target/proc/");
}
void mountDev()
{
    system("mount --bind /dev/ /media/target/dev/");
}

void mountSys()
{
    system("mount --bind /sys/ /media/target/sys/");
}
// Metodo para crear la particion SWAP.
void MakeSwap()
{
	system(createSwap.c_str());
	system(EnableSwap.c_str());
}
#endif // DEMENCIAOSDEBINSTALL
