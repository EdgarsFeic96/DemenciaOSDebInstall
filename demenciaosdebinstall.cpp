/// Demencia OS Installer by hhk02

#include "demOSInstaller20.h"

using namespace std;

// system(): Esta función nos permite ejecutar programas de linea de comandos.

// Metodo de proceso de instalación
void InstallProcess()
{
    cout << "Installing...." << endl;
	// Descomprimir el archivo squashfs RESPONSABLE de descomprimir el sistema en el destino
	// string exec4 = "unsquashfs -f -d /media/target/ /media/cdrom/casper/filesystem.squashfs" para ubuntu
	system(unsquashfs.c_str());

	if(isEFI==false)
	{
		// Instalar gestor de arrange GRUB en modo legacy
		cout << "Installing bootloader (grub)" << endl;
		// Comando grub-install --target=i386-pc (modo legacy) --root=directry= (ruta de punto de montaje)
        system(installGRUBLegacy.c_str());
		// Cambiar a la instalación de destino y ejecutar update-grub para generar la configuración del GRUB
        cout << "Use genfstab -U / >> /etc/fstab and finally use update-grub\n" << endl;
		system("chroot /media/target");
		cout << "Installation complete!" << endl;

    } else {
        mountDev();
        mountProc();
        mountSys();
        system("clear");
        cout << "FIRST COMMAND: You are right now in the new installation of DemenciaOS (chroot).\n put mkdir -v /mnt/boottemp and cp -rv /boot /mnt/boottemp\n" << endl;
        cout << "SECOND COMMAND: put mount /dev/sdx1 /boot or /dev/nvme0n1p1 /boot (NVMe) and grub-install --target=x86_64-efi --efi-directory=/boot\n, open an other terminal and login with root with sudo -i or sudo su and write genfstab -U /media/target/ >> /media/target/etc/fstab\n" << endl;
        cout << "THIRD COMMAND: put cp -rv /mnt/boottemp/boot/* /boot/ and finally. put update-grub and finally use command to exit. \n " << endl;
        system("chroot /media/target");
        cout << "Installation complete you can reboot with sudo reboot or systemctl reboot" << endl;

	}
}

// // Metodo al iniciar el menu de 1.- Install
void Install()
{
    system("clear");
    system("lsblk");

    cout << "Write you disk here: " << endl;
    cin >> disk;

    if(disk=="")
    {
        Install();
    }
    else {
            try {
                // Iniciar CFDISK
                cout << "Enter to cfdisk " + disk << endl;
                //string runapt = "apt install gparted -y";
                //system(runapt.c_str());
                system(fdiskrun.c_str());
                cout << "OK" << endl;
                cout << "You do want use SWAP? (yes/no)" << endl;
                cin >> swapoption;
                cout << "Is EFI? (yes/no)" << endl;
                cin >> efioption;
                // Comprobar si es EFI o no
                if (efioption=="yes")
                {
                    isEFI = true;
                    cout << "EFI Partition: " << endl;
                    cin >> efipart;
                }
                else {
                    isEFI = false;
                }
                // Comprobar si usa la swap o no
                if (swapoption=="yes")
                {
                    usingSwap=true;
                }
                else {
                    usingSwap=false;
                }
                // Comprobar si es EFI o no
				if(isEFI == true)
				{
					if (startsWith(disk,"/dev/nvme0n1"))
                    {
                        disk = disk + "p";
                    } else {
                        disk = disk;
                    }
					// Ejecutar metodos para el EFI
                    cout << "Making partitions" << endl;
					system(runMkdirTargetDir.c_str());
					system(mkBootDir.c_str());
					system(mkEFIpart.c_str());
					system(mkRootPart.c_str());
					system(mountRoot.c_str());
					cout << "Success!" << endl;
					InstallProcess();
				// Si no es asi inicia las ordenes para el modo Legacy (BIOS)
				} else {
					cout << "Formating partitions" << endl;
					system(mkRootLegacy.c_str());
					cout << rootpart + " it's created sucessfully!" << endl;
					system("mkdir /media/target");
					cout << "Mounting partitions...." << endl;
					system(mountLegacyRoot.c_str());
				if (usingSwap==true){
					cout << "Please specify the swap partition ex: /dev/sda3" << endl;
					cin >> swappart;
					cout << "Creating swap" << endl;
					MakeSwap();
					cout << "Swap created sucessfully" << endl;
				}
				}
            }
            catch (string ex)
            {
                cout << ex << endl;
            }
            }
}
// Metodo inicial
int main()
{
    cout << "Welcome to the Demencia OS Installer. What do you want?" << endl;
    cout << "1.- Install" << endl;
    cout << "2.- Exit" << endl;
    cout << "Do you want?" << endl;
    cin >> option;

    if (option==2)
    {
        system("exit");
    }

    if (option>=3)
    {
        main();
    }

    if (option==1)
    {
        Install();
    }
}
