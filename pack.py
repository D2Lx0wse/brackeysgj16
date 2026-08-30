import shutil
import os

print("build game set to release. done? y/n")
answer=input()
if answer=="y":
    print("packing to staging")
    f = open("./packing/brackeys.exe", "w")
    shutil.copyfile("./brackeys/x64/Release/brackeys.exe", "./packing/brackeys.exe")

else:
    print("quitting")