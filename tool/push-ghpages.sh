echo "Pulling gh-pages"
PWD=pwd
cd ../../
mkdir gh-pages
cd gh-pages
git init
git config --system http.sslverify false
git pull https://github.com/Lionel07/elementOS.git --progress
git config --system http.sslverify true
git checkout gh-pages
pwd
cp ../elementOS/kernel.elf ./kernel.elf
git add kernel.elf
sudo git commit -m "Updated kernel image [no ci]"
git push
cd ../
rm -r gh-pages
cd elementOS
