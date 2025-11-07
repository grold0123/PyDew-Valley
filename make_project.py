import subprocess,pathlib,sys

base_dir = pathlib.Path(r"C:\projects\PyDew-Valley")
src_path = base_dir/"src"
build_path = base_dir/"build"


project_name = sys.argv[1]
if project_name:
    project_path = src_path/project_name
    project_path.mkdir(exist_ok=True)
    cpp_file = project_name + ".cpp"
    (project_path/cpp_file).touch(exist_ok=True)
    with open(project_path/cpp_file,"w") as file:
        file.write("/**********************************\n")
        file.write(project_name)
        file.write("\n**********************************/\n")
    subprocess.run(["code",f"{str(project_path)}/{project_name}.cpp"])

