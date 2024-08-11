from cs50 import get_string


def main():
    '''uses Coleman-Liau index to grade difficulty of a text'''

    # Ask user for text
    text = get_string("Please enter text:\n")

    # Calculate L and S
    words = count_words(text)
    L = count_letters(text) / words * 100
    S = count_sentences(text) / words * 100

    # Calculate index
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # interpret and print result
    print_grade(index)


def count_letters(text):
    '''return number of alphabetic letters in text'''

    letter_count = 0
    for i in range(0, len(text)):
        if text[i].isalpha():
            letter_count += 1

    return letter_count


def count_words(text):
    '''return number of words in text'''

    word_count = 1
    for i in range(0, len(text)):
        if text[i] == " ":
            word_count += 1

    return word_count


def count_sentences(text):
    '''return number of sentences in text'''

    sentence_count = 0
    for i in range(0, len(text)):
        if text[i] in [".", "!", "?"]:
            sentence_count += 1

    return sentence_count


def print_grade(index):
    '''inteprets index and prints grade'''

    if index > 15:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")


main()