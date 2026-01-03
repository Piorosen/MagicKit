#%%
with open('test.asm', 'r') as f:
    d = f.readlines()
d = d[6:]
d = [line.strip() for line in d]
d
#%%
d = list(filter(lambda x: x != '', d))
d = list(map(lambda x: x.split(':')[1].strip().split(' ')[0], d))
d = ''.join(d)

hex_str = d

if len(hex_str) % 2 != 0:
    raise ValueError(f"hex 길이가 짝수가 아닙니다(현재 {len(hex_str)}). 1바이트(2글자) 단위가 깨집니다.")

# 1바이트(2글자)씩 쪼개서 전체를 reverse
bytes_ = [hex_str[i:i+2] for i in range(0, len(hex_str), 2)]
bytes_.reverse()

# C++용 "\x.." 문자열 생성
c_str = "".join(f"\\x{b}" for b in bytes_)

print('unsigned char code[] = "' + c_str + '";')
print("size_t code_len = sizeof(code) - 1;")


# %%
