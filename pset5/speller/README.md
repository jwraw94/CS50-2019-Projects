# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

The longest word in the dictionary - an invented long word said to mean a lung disease caused by inhaling very fine ash and sand dust.


## According to its man page, what does `getrusage` do?

Get the resource usage for a process or thread

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

In order to use less memory. Passing a reference to the data means that a copy of before / after will not need to be created on the stack.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

The for loop reads the specified file, character by character, using fgetc. fgetc is initialised to read the first character of the input 'file', until the end of the file. It moves through the file by reading the next char from the stream, and moving the cursor along each iteration. For each alphabetical character that it finds, the if loop appends the character to the 'word' at the current index (the index increments +1 for each relevant letter found). If a number/non alphabetical char is found, or the word is too long, the word is discarded. If the word string has characters, and the next char that fgetc identifies is not alphabetical, it must be the end of the word, so it is terminated with a \0, and the word is compared for it's spelling.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

To have more control over what characters are being considered, and how many. fscanf can read too many characters, such as commas, full stops etc. This can cause a string that is longer than it should be/incorrect. The input file will not have guaranteed consistent word endings.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

Declaring the parameters for check and load as constants prevents them being accidentally edited.
