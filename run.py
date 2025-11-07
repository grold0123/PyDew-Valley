import subprocess,pathlib,sys

base_dir = pathlib.Path(r"C:\projects\PyDew-Valley")
src_path = base_dir/"src"
build_path = base_dir/"build"

project_name = sys.argv[1]
cpp_files = []
if project_name:
    project_path = src_path/project_name
    if project_path in [path for path in src_path.iterdir()]:
        cpp_files = [str(file) for file in project_path.glob("*.cpp")]
        args = [
            'g++',
            *cpp_files,
            '-o',
            f'build/{project_name}',
            '-Iinclude',
            '-Llib',
            '-lSDL3',
            '-lSDL3_image'
            ]
        result = subprocess.run(args)
        if result:
            print(f"\n\nOpening: {project_name}.exe ")
            subprocess.run(f"build/{project_name}.exe")
        else:
            print("\n\nBuild not successful")
    


