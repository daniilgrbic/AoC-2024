import itertools

NUM_PAD = {
    key: (row, col) 
        for row, keys in enumerate('789\n456\n123\n_0A'.splitlines())
        for col, key in enumerate(keys) if key != '_'
}

DIR_PAD = {
    key: (row, col) 
        for row, keys in enumerate('_^A\n<v>'.splitlines())
        for col, key in enumerate(keys) if key != '_'
}

def sequences_from_pos_to_letter(key_pad, start_pos, target_letter):
    sequences = [(start_pos, '')]
    target = key_pad[target_letter]

    while sequences:
        curr_pos, path = sequences.pop()
        if curr_pos == key_pad[target_letter]:
            yield path
            continue

        column_move = target[1] - curr_pos[1]
        if column_move != 0:
            next_pos = curr_pos[0], curr_pos[1] + (column_move // abs(column_move))
            if next_pos in key_pad.values():
                key = '>' if column_move > 0 else '<'
                sequences.append((next_pos, path + key))

        row_move = target[0] - curr_pos[0]
        if row_move != 0:
            next_pos = curr_pos[0] + (row_move // abs(row_move)), curr_pos[1]
            if next_pos in key_pad.values():
                key = 'v' if row_move > 0 else '^'
                sequences.append((next_pos, path + key))

cache = {
    # (key_pad, deep, code) -> minimal_sequence_length
}

def minimal_sequence_length(key_pad, code, depth):
    if (len(key_pad), code, depth) in cache:
        return cache[len(key_pad), code, depth]

    if depth == 0:
        cache[len(key_pad), code, depth] = len(code)
        return len(code)

    from_position = key_pad['A']
    minimal_length = 0
    for to_letter in code:
        minimal_length += min(minimal_sequence_length(DIR_PAD, sequence  + 'A', depth - 1)
            for sequence in sequences_from_pos_to_letter(key_pad, from_position, to_letter))
        from_position = key_pad[to_letter]

    cache[len(key_pad), code, depth] = minimal_length
    return minimal_length
