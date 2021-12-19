# sw_systems_hw3
This assignment focuses on Strings and miminum continuous sequences.
The program receives a String word and String text and engages 3 functions. 
1. Gematria - This function calculates the gematria of the word and iterates through the text, printing every minimum continuous squence with the same gematria value.
2. Atbash - This function calculates the Atbash version of the word, reverses the word, then finds the Abash version of the reversed word ass well. Then the function iterates through the txt and prints all minimun sequences that are the Atbash word, or Atbash reversed word.
3. Anagram - This function iterates through the text, skipping over spaces until it finds a char that is in word. That char now turned into a space. If we reach a char that is not in word, break. If the amount of times we didn't break is equal to the size of word, and the potential word has become all spaces at this point, we have reached a minimun continuous sequence containing only the chars of word and we print it. 
