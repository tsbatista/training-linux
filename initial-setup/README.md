# Creating a Virtual Machine

The first step is the creation of a simple virtual machine that will be used to run our exercises.

Before we start, you will need to install the following pre-requisites - please download and install them before the first training session:

1. VirtualBox
1. Vagrant


## Virtualbox

You can get it at https://www.virtualbox.org/ or from your favorite software repositories. You should be able to create and boot a minimal VM (even without an operating system). Note that if you are using linux and have enabled secure boot you will either need to disable it (recomended), or sign the modules with a registered private key (which will not be covered in this session)

## Vagrant

In order to use Vagrant, you will need to install it from https://www.vagrantup.com/. For this course you will need version >= 2.2.10, some of the required features do not work at all with previous versions.

# Procedure

1. Install the VBGuest plugin running `vagrant plugin install vagrant-vbguest`
1. `cd` to the directory with the `Vagrantfile` 
1. run `vagrant up`
1. wait... wait... wait...
1. run `vagrant ssh`

After this procedure you should be working on a terminal in your just created virtual machine - the prompt should read: 

`[vagrant@localhost ~]$`

# Alternative procedure (not recommended)

Create a VM in virtualbox, perform a minimal centos 8 instal and finally add 3 extra disks to the IDE controller - that should allow you to follow most of the exercises, but it will requiere you to manually install a lot more packages than those that will be installed by your coleagues. It will also potentially limit your ability to ssh into the VM, forcing you to use the Virtualbox UI.

## Some other commands you may need

To perform a shutdown of your VM you can either shut it sown from within the ssh session using `shutdown -h now`, from the host you can use the Virtualbox UI or you can run `vagrant halt`

When you are done with the session, or if you want to start over, you can delete the VM either via the VirtualBox UI or by running `vagrant destroy` - Note that given that we are using an experimental feature, you may fail to re-create the VM - if that is the case you will need to find the culprit files in the VirtualBox directory and manually delete them.

For more useful vagrant commands, visit https://www.vagrantup.com/docs/cli