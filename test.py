#%%
with open('test.asm', 'r') as f:
    d = f.readlines()
d = d[6:]
#%%
#%%
# 1. Parsing adjustments
# (Optional: Filter only lines that look like instructions to avoid header issues)
d = [line.strip() for line in d if ':' in line] 
# Locate the start of the code (skipping file format headers)
# We assume the code starts after the first few lines, or just filter valid hex lines
d = list(filter(lambda x: len(x) > 0 and '\t' in x, d))

# 2. Extraction
# Extract the hex part (e.g., "d10043ff")
# Assumes format: "300: d10043ff \tsub..."
d = list(map(lambda x: x.split(':')[1].strip().split()[0], d))
hex_str = ''.join(d)

if len(hex_str) % 8 != 0:
    raise ValueError(f"Hex length error: {len(hex_str)}. Must be multiple of 8 characters.")

# 3. Create 8-character chunks (4 bytes each)
bytes_ = [hex_str[i:i+8] for i in range(0, len(hex_str), 8)]

# === CRITICAL FIXES ===
# 1. REMOVED: bytes_.reverse() 
#    We must preserve the instruction flow (Top -> Bottom).

# 2. MODIFIED: Byte Swapping for Little Endian
#    Input:  d10043ff (MSB...LSB)
#    Output: \xff\x43\x00\xd1 (LSB...MSB)
c_str = "".join(f"\\x{b[6:8]}\\x{b[4:6]}\\x{b[2:4]}\\x{b[0:2]}" for b in bytes_)

print('unsigned char code[] = "' + c_str + '";')
# Note: subtracting 1 from sizeof usually needed for string null-terminator in C, 
# but for raw bytes, use explicit length or don't treat as string.
print(f"size_t code_len = {len(bytes_) * 4};") 
#%%