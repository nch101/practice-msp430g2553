TEMP_DIR=temp_dir
TOOLCHAIN_DIR=/opt/msp430-gcc

# Install necessary packages
sudo apt update 
sudo apt install wget p7zip-full -y

# Create temporatory directory to store msp430 toolchain
mkdir ${TEMP_DIR}
cd ${TEMP_DIR}

# Get msp430 toolchain
wget https://dr-download.ti.com/software-development/ide-configuration-compiler-or-debugger/MD-LlCjWuAbzH/9.3.1.2/msp430-gcc-full-linux-x64-installer-9.3.1.2.7z
7z x *
sudo ./msp430-gcc-full-linux-x64-installer-9.3.1.2.run --prefix ${TOOLCHAIN_DIR}

# Remove temporatory directory
cd ..
sudo rm -rf ${TEMP_DIR}

# Done
echo "Done\n"
