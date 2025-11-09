import subprocess

base_dir = r"C:\projects\PyDew-Valley"


args = [
    ['git','add',base_dir],#git add
    ['git','commit','-m','update'],#git commit
    ['git','push'],#git push
]

for arg in args:
    print('\n\n')
    result = subprocess.run(arg)
    if result.returncode == 0:
        continue
    break;
    
