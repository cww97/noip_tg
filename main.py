import pypandoc
import os
import re
import fnmatch

# modify this on different Computer
output_path = "C:\\Users\\cww97\\Desktop\\output\\"


def convert_mds(cwd, dir_name):
    os.chdir(cwd + '\\' + dir_name)
    
    files = os.listdir()
    files = fnmatch.filter(files, '*.md')
    for file in files:
        file_name = file.replace('.md', '')
        output_name = output_path + dir_name[:2] + 'P-' + file_name
        os.system('pandoc -s %s -o %s.docx' %(file, output_name))
        print(file, '-->', file_name, '.docx')

def main():
    cwd = os.getcwd()
    dirs = os.listdir()
    for dir in dirs:
        if (re.match(r"\d\d\-.*", dir)):
            convert_mds(cwd, dir)

if __name__ == '__main__':
    main()
