Assumptions for Q1:
    1. If length of file is zero bytes, the progress bar directly prints 100%.
    2. If the length of the file is greater than 100000, then chunk size is 100000.
    3. If the length of the file is greater than 1000, less than 100000, then chunk size is 1000.
    4. If length of the file is less than 1000, then chunk size if 1.

Assumptions for Q2:
    1. If length of file is zero bytes, the progress bar directly prints 100%.
    2. If the length of the file is greater than 100000, then chunk size is 100000.
    3. If the length of the file is greater than 1000, less than 100000, then chunk size is 1000.
    4. If length of the file is less than 1000, then chunk size if 1.
    5. All parts of the file, to be reversed and not to be reversed are handled separately/

Assumptions for Q3:
    1. If directory is not created, permissions of directory are not printed. "Can't open directory" is printed instead.
    2. If newFile is not created, permissions of file are not printed. "Can't open newFile" is printed instead.
    3. If oldFile is not created, permissions of the file are not printed. "Can't open oldFile" is printed instead.
