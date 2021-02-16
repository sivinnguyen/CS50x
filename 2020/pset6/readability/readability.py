from cs50 import get_string
import re


def main():
    text = get_string("Text: ")

    l = cLetters(text)
    w = cWords(text)
    s = cSentences(text)

    L = (l * 100) / w
    S = (s * 100) / w
    index = 0.0588 * L - 0.296 * S - 15.8

    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(index)}")


def cLetters(text):  # Count characters
    count = 0
    for c in text:
        if (c >= 'a' and c <= 'z') or (c >= 'A' and c <= 'Z'):
            count += 1
    return count


def cWords(text):  # Count words
    words = text.split()
    return len(words)


def cSentences(text):  # Count sentences
    sentences = re.split(r'[.!?]+', text)  # Ko biet tai sao ket qua luon du mot phan tu '' <= boi vi dau cau cuoi cung cua doan van
    return len(sentences) - 1


main()  # Call main