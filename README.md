# 🎵 MP3 Tag Reader & Editor (C Project)

The **MP3 Tag Reader & Editor** is a command-line application developed in **C programming language** that allows users to **view and modify metadata (ID3 tags)** of MP3 files. The project works by directly reading and manipulating the **binary structure of MP3 files**, specifically the **ID3v2 tag frames**, to extract and update song information such as Title, Artist, Album, Year, and Genre.

---

## 🚀 Features
- View MP3 metadata (Title, Artist, Album, Year, Genre)
- Edit MP3 tags using command-line options
- Supports only `.mp3` file validation
- Uses **temporary file handling** for safe editing
- Handles **big-endian to little-endian conversion**
- Efficient parsing of ID3 frames

---

## 🛠️ Technologies Used
- C Programming
- File Handling (`fread`, `fwrite`, `fseek`)
- Structures and Pointers
- String Handling (`string.h`)

---

## ⚙️ Working
The program reads the **ID3 header (first 10 bytes)** and then processes individual frames like:
- `TIT2` → Title  
- `TPE1` → Artist  
- `TALB` → Album  
- `TYER` → Year  
- `TCON` → Genre  

For editing, it creates a **temporary file**, modifies the required frame, copies remaining data, and safely replaces the original file.

---

## ▶️ Usage

### Compile
```bash
gcc *.c
View Tags
./a.out -v file.mp3
Edit Tags
./a.out -e file.mp3 -t "New Title"
./a.out -e file.mp3 -a "Artist Name"
./a.out -e file.mp3 -A "Album Name"
./a.out -e file.mp3 -y "2024"
./a.out -e file.mp3 -c "Genre"


📸 Sample Output
View Option Selected ✅

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MP3 TAG READER AND EDITOR ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Title   -> Shape of You
Artist  -> Ed Sheeran
Album   -> Divide
Year    -> 2017
Genre   -> Pop


📚 Learning Outcomes
Understanding of binary file processing
Knowledge of ID3 tag structure
Hands-on experience with file handling in C
Debugging segmentation faults and memory issues
Writing modular and structured code

👩‍💻 Author
Samiksha Mane
B.Tech Electronics & Telecommunication Engineering
