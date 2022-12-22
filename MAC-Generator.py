# https://github.com/Chainski/MACGenerator
from random import choice
import traceback
import os
import sys
import ctypes
import colorama
import requests
import threading
import pystyle
from colorama import *
import pystyle
from pystyle import *
from time import time


os.system('cls')
os.system('mode con: cols=120 lines=50')
ctypes.windll.kernel32.SetConsoleTitleW("MAC Generator")
string = '0123456789ABCDEF'
file = 'MacAddresses.txt'

def duplicate(path):
  f = open(path, 'r', errors='ignnore').readlines()
  old = len(f)
  new_f = set(f)
  new = len(new_f)
  o = open(path, 'w')
  for line in new_f:
    o.write(line)
  print(f"\033[0;92m[*] {old - new} Duplicate(s) have been removed!")
  print(f"\033[1;31m[*] Finished! Results have been saved in {path}")
  
  


def mode1():
  mac = ''.join(choice(string) for _ in range(6))
  return f"00:1A:79:{mac[0:2]}:{mac[2:4]}:{mac[4:6]}\n"


def mode2(custom):
  list1 = []
  for letter in custom:
    if letter == '*':
      letter = letter.replace('*', ''.join(choice(string)))
    list1.append(letter)
  return ''.join(list1) + "\n"


def generator(mode, custom):
  t1 = time()
  with open(file, 'w') as o:
    for x in range(number):
      if mode == '1':
        o.write(mode1())
      elif mode == '2':
        o.write(mode2(custom))
      print(f"\033[0;92m[*] Generated: {x + 1} MAC addresses", end='\r')
  print("\n\033[1;31m[*] Removing duplicates...\n", end='\r')
  duplicate(file)
  t2 = time()
  elapsed = t2 - t1
  print('\033[0;94m[*] Finished in %f seconds !' % elapsed)


if __name__ == '__main__':
  try:
    
    print(f"""  
        
        {Fore.LIGHTBLUE_EX}███╗   ███╗ █████╗  ██████╗     ██████╗ ███████╗███╗   ██╗███████╗██████╗  █████╗ ████████╗ ██████╗ ██████╗ 
        {Fore.LIGHTRED_EX}████╗ ████║██╔══██╗██╔════╝    ██╔════╝ ██╔════╝████╗  ██║██╔════╝██╔══██╗██╔══██╗╚══██╔══╝██╔═══██╗██╔══██╗ 
        {Fore.LIGHTBLUE_EX}██╔████╔██║███████║██║         ██║  ███╗█████╗  ██╔██╗ ██║█████╗  ██████╔╝███████║   ██║   ██║   ██║██████╔╝ 
        {Fore.LIGHTRED_EX}██║╚██╔╝██║██╔══██║██║         ██║   ██║██╔══╝  ██║╚██╗██║██╔══╝  ██╔══██╗██╔══██║   ██║   ██║   ██║██╔══██╗ 
        {Fore.LIGHTBLUE_EX}██ ║╚═╝ ██║██║  ██║╚██████╗    ╚██████╔╝███████╗██║ ╚████║███████╗██║  ██║██║  ██║   ██║   ╚██████╔╝██║  ██║ 
        {Fore.LIGHTRED_EX}╚═╝     ╚═╝╚═╝  ╚═╝ ╚═════╝     ╚═════╝ ╚══════╝╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝ 
        
                                      {Fore.LIGHTGREEN_EX}╔═══════════════════════════════════════════════╗
                                      {Fore.WHITE}║      IPTV MAC ADDRESS GENERATOR 1.0.0.0       ║
                                      {Fore.LIGHTGREEN_EX}║             coded by CHAINSKI TOOLS           ║
                                      {Fore.WHITE}║        For Educational Purposes Only          ║
                                      {Fore.LIGHTGREEN_EX}║   https://github.com/Chainski/MAC-Generator   ║
                                      {Fore.WHITE}╚═══════════════════════════════════════════════╝      
         

              """)
                  
    Write.Print("\n [*] This program will generate random MAC addresses select a mode from the option below to continue \n", Colors.blue_to_white, interval=0.01)
    print()    
    mode = Write.Input(""" Select Mode:
    1. [*] Default: 00:1A:79:**:**:**
    2. [*] Custom (Example: 00:1A:79:*8:1B:**)
    > """, Colors.white_to_red, interval=0.0025)
    custom = Write.Input("[*] Enter custom mode: ", Colors.blue_to_white, interval=0.0025) if mode == '2' else None
    number = int(Write.Input("[*] Enter the amount of Macs to generate: ", Colors.blue_to_white, interval=0.0025))
    generator(mode, custom)
  except:
    print(traceback.format_exc())
    Write.Print("\n[*] Something went wrong, please try again.\n", Colors.blue_to_white, interval=0.0025)
  input("\033[0;92m[*] Press ENTER to close. \n")