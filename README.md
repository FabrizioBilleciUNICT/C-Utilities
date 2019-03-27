# Utilities in C

A group of utilities written in C and executable in an UNIX terminal.

* ### renamer.c
  This program renames all the occurrences in all sub-directories.<br>
  Usage: ./a.out 'rootdir' old_filename new_filename

* ### substr_mantainer.c
  This program remove all files which names NOT contain the selected substring<br>
  Usage: ./a.out 'rootdir' substring_to_maintain

* ### substr_remover.c
  This program remove all files which names contain the selected substring<br>
  Usage: ./a.out 'rootdir' substring_to_remove
  
## Usage Example
I personally use them to add resources from material.io/tools/icons/ to my Android apps: select and download a lot of icons from material.io, unzip them and then remove from all sub-dirs (drawable-mdpi/hdpi/xhdpi/etc) unused density (example: only want 24) and rename a particular file in each sub-dirs (drawable-mdpi/hdpi/xhdpi/etc) at once.  

