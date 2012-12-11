
static unsigned char const interpolationTable[768] =
{
     31,  36,  70,  34,  36,  69,  36,  37,  69,  39,  37,  69,  43,  38,  69,  46, 
     37,  69,  49,  38,  69,  52,  38,  69,  56,  38,  68,  60,  38,  68,  63,  38, 
     68,  67,  39,  68,  71,  38,  68,  76,  39,  67,  79,  39,  66,  84,  40,  67, 
     88,  40,  66,  93,  40,  65,  98,  41,  65, 102,  40,  64, 108,  41,  63, 113, 
     42,  63, 118,  42,  63, 122,  41,  61, 128,  41,  60, 134,  42,  59, 140,  42, 
     58, 144,  42,  57, 151,  42,  55, 156,  42,  54, 162,  42,  53, 168,  42,  51, 
    173,  42,  50, 179,  42,  49, 184,  42,  47, 189,  41,  46, 195,  41,  45, 198, 
     40,  43, 203,  41,  42, 208,  40,  40, 211,  39,  38, 216,  39,  37, 220,  38, 
     36, 223,  38,  35, 226,  38,  33, 229,  37,  33, 229,  39,  32, 230,  41,  33, 
    230,  44,  32, 230,  46,  33, 230,  50,  33, 230,  52,  33, 230,  56,  33, 231, 
     58,  33, 231,  61,  32, 231,  65,  33, 231,  69,  33, 232,  73,  32, 232,  76, 
     33, 233,  80,  33, 234,  86,  34, 234,  89,  34, 235,  93,  33, 235,  97,  34, 
    236, 101,  34, 236, 105,  34, 237, 108,  33, 238, 114,  34, 238, 117,  33, 239, 
    121,  33, 240, 126,  33, 240, 130,  33, 241, 134,  32, 241, 138,  31, 243, 142, 
     33, 243, 146,  32, 243, 149,  31, 245, 154,  31, 246, 158,  30, 246, 162,  30, 
    246, 164,  29, 248, 167,  29, 247, 169,  28, 248, 172,  26, 249, 176,  27, 249, 
    177,  26, 249, 179,  26, 250, 183,  25, 251, 185,  25, 251, 187,  23, 252, 191, 
     23, 252, 192,  22, 253, 194,  21, 253, 197,  20, 254, 199,  19, 254, 201,  19, 
    255, 203,  17, 255, 205,  15, 255, 207,  14, 255, 209,  12, 255, 211,  11, 255, 
    213,   8, 255, 214,   7, 255, 216,   7, 255, 217,   6, 255, 219,   5, 255, 219, 
      4, 255, 221,   2, 255, 223,   1, 255, 224,   0, 255, 225,   0, 254, 226,   0, 
    253, 226,   0, 253, 227,   0, 253, 228,   0, 252, 228,   0, 251, 229,   0, 250, 
    229,   0, 249, 229,   0, 249, 230,   0, 248, 231,   1, 247, 231,   2, 246, 230, 
      3, 246, 231,   3, 245, 230,   5, 244, 231,   6, 243, 230,  14, 242, 230,  22, 
    241, 229,  29, 239, 228,  33, 237, 228,  39, 236, 227,  45, 235, 227,  49, 233, 
    226,  55, 231, 224,  58, 230, 224,  65, 227, 222,  67, 225, 221,  74, 223, 219, 
     77, 221, 218,  81, 220, 217,  85, 217, 215,  90, 214, 213,  93, 212, 211,  98, 
    209, 210, 102, 207, 207, 105, 204, 205, 109, 201, 203, 113, 198, 201, 116, 196, 
    199, 119, 193, 197, 123, 190, 194, 125, 187, 192, 128, 184, 190, 132, 181, 187, 
    135, 179, 185, 136, 176, 183, 139, 173, 180, 142, 170, 177, 145, 167, 175, 147, 
    164, 172, 148, 162, 170, 151, 159, 168, 153, 156, 165, 154, 152, 162, 155, 151, 
    161, 158, 148, 158, 158, 146, 156, 160, 142, 152, 161, 139, 150, 161, 138, 148, 
    163, 134, 145, 164, 132, 143, 164, 130, 141, 165, 126, 138, 166, 124, 136, 167, 
    122, 133, 167, 119, 130, 167, 117, 128, 168, 114, 126, 167, 112, 123, 167, 110, 
    122, 168, 108, 119, 168, 106, 116, 168, 104, 114, 168, 102, 112, 168,  99, 110, 
    167,  99, 109, 168,  97, 106, 168,  94, 104, 167,  92, 102, 167,  91, 101, 167, 
     90,  99, 167,  88,  97, 166,  86,  95, 166,  84,  94, 165,  83,  92, 165,  81, 
     91, 165,  81,  90, 164,  80,  89, 164,  79,  88, 164,  77,  86, 162,  74,  84, 
    160,  73,  82, 159,  72,  80, 157,  69,  79, 155,  68,  78, 154,  67,  76, 153, 
     66,  74, 151,  64,  73, 149,  63,  71, 148,  60,  70, 146,  60,  68, 144,  58, 
     66, 142,  58,  66, 140,  57,  65, 138,  56,  63, 135,  55,  62, 134,  54,  61, 
    132,  52,  60, 130,  51,  58, 127,  50,  57, 125,  49,  56, 123,  49,  55, 121, 
     49,  55, 119,  48,  54, 117,  47,  53, 115,  46,  52, 113,  45,  51, 111,  45, 
     51, 109,  44,  49, 106,  43,  49, 104,  43,  48, 103,  42,  48, 101,  41,  47, 
     99,  40,  46,  96,  39,  45,  94,  38,  44,  92,  39,  44,  91,  39,  43,  89, 
     38,  43,  88,  38,  43,  86,  36,  42,  85,  37,  42,  84,  36,  41,  81,  35, 
     40,  80,  35,  40,  79,  34,  39,  77,  33,  39,  76,  33,  38,  75,  32,  38, 
     74,  32,  38,  73,  31,  37,  72,  31,  36,  71,  31,  37,  71,  31,  37,  70
  };