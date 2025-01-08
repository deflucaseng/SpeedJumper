import os
from pathlib import Path

def print_directory_structure(directory, prefix=""):
    """
    Recursively prints the directory structure starting from the given directory.
    
    Args:
        directory (str): Path to the directory to print
        prefix (str): Prefix for the current line (used for indentation)
    """
    # Get the directory items
    try:
        items = sorted(os.listdir(directory))
    except PermissionError:
        print(f"{prefix}[Permission Denied]")
        return
    except FileNotFoundError:
        print(f"Error: Directory 'speedjumper' not found")
        return

    # Print each item
    for i, item in enumerate(items):
        path = os.path.join(directory, item)
        is_last = i == len(items) - 1
        
        # Choose the appropriate prefix characters
        if is_last:
            branch = "└──"
            new_prefix = prefix + "    "
        else:
            branch = "├──"
            new_prefix = prefix + "│   "
            
        # Print the current item
        print(f"{prefix}{branch} {item}")
        
        # Recursively print directories
        if os.path.isdir(path):
            print_directory_structure(path, new_prefix)

if __name__ == "__main__":
    speedjumper_path = Path("speedjumper")
    print(f"Directory structure of 'speedjumper':")
    print_directory_structure(speedjumper_path)