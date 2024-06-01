def add_newline(text):
    words = text.split()
    result = ''
    count = 0
    for word in words:
        if count + len(word) + 1 <= 60:
            result += word + ' '
            count += len(word) + 1
        else:
            result += '\n' + word + ' '
            count = len(word) + 1
    return result.strip()

# Example usage:
sentence = "Good name in man and woman, dear my lord, Is the immediate jewel of their souls: Who steals my"
formatted_sentence = add_newline(sentence)
print(formatted_sentence)
