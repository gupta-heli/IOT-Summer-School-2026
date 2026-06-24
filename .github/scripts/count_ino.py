import os

def count_ino_files():
    count = 0
    ino_files = []
    # Traverse directories recursively
    for root, dirs, files in os.walk('.'):
        # Exclude hidden directories like .git
        dirs[:] = [d for d in dirs if not d.startswith('.')]
        for file in files:
            if file.endswith('.ino'):
                count += 1
                ino_files.append(os.path.join(root, file))
                
    print("========================================")
    print(f"Total .ino files found in repository: {count}")
    print("========================================")
    for path in ino_files:
        print(f"- {path}")
    print("========================================")

if __name__ == '__main__':
    count_ino_files()
