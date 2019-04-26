const uint8_t spTARGET[] PROGMEM = {0x0A,0xD8,0x5C,0x4D,0x03,0x25,0x8D,0xA9,0x24,0x5A,0x52,0xB6,0x22,0x85,0x31,0x1F,0xDC,0xD2,0xF2,0xB4,0x4C,0xDB,0xE5,0xCA,0xC8,0x52,0x0B,0xEE,0xA6,0xC7,0x2D,0xCF,0x53,0x69,0x43,0x6E,0xA5,0xBA,0x94,0x80,0x2A,0xAA,0x65,0xFA,0x1C,0x88,0x36,0x23,0x51,0x1B,0xEB,0x30,0xF4,0xB0,0x36,0x6B,0xA8,0x51,0x24,0x3D,0xD6,0xAC,0xA1,0x84,0x44,0x4F,0x7F,0xD4,0xE6,0x41,0x46,0x70,0x62,0x23,0x02,0xA7,0x28,0x55,0xA1,0x1A,0x00,0xA0,0x80,0x21,0xDD,0x18,0xB0,0xB9,0xDA,0xFF,0x03};
const uint8_t spREADY[] PROGMEM = {0x6A,0xB4,0xD9,0x25,0x4A,0xE5,0xDB,0xD9,0x8D,0xB1,0xB2,0x45,0x9A,0xF6,0xD8,0x9F,0xAE,0x26,0xD7,0x30,0xED,0x72,0xDA,0x9E,0xCD,0x9C,0x6D,0xC9,0x6D,0x76,0xED,0xFA,0xE1,0x93,0x8D,0xAD,0x51,0x1F,0xC7,0xD8,0x13,0x8B,0x5A,0x3F,0x99,0x4B,0x39,0x7A,0x13,0xE2,0xE8,0x3B,0xF5,0xCA,0x77,0x7E,0xC2,0xDB,0x2B,0x8A,0xC7,0xD6,0xFA,0x7F,};
const uint8_t spGREAT2[] PROGMEM = {0x6A,0xD1,0x55,0x75,0xC2,0x95,0xAA,0x5D,0x0C,0xD1,0x4E,0x55,0x66,0x56,0x35,0x58,0x3B,0xD5,0x99,0x99,0xCD,0x24,0x9F,0x50,0x77,0x61,0x0A,0x03,0xAB,0x4C,0xB2,0xB5,0x3E,0x2D,0x2C,0x0B,0xCD,0xBA,0xBA,0x52,0x35,0xC4,0x2D,0xDB,0x6A,0x9B,0x2B,0xD1,0xB4,0x2D,0xAB,0x1A,0xB6,0x88,0xD3,0xB7,0xAC,0x7C,0xD8,0x44,0xAE,0x5C,0xB3,0xD2,0xE1,0x1D,0x34,0x73,0xC9,0x48,0x47,0x12,0x34,0xEB,0x26,0x26,0xDB,0x8C,0x59,0xAD,0x1A,0x21,0x70,0x8A,0x52,0x15,0xAA,0x01,0xE0,0x80,0x2D,0xC3,0x1C,0xF0,0xAD,0xFB,0xFF,0x03};

const uint8_t spINTRO[] PROGMEM =  {0x80,0xA0,0x20,0x65,0xDB,0x30,0x0E,0x6B,0x83,0x94,0x6D,0x83,0xF5,0xA1,0x75,0x26,0x27,0x95,0x3B,0xAD,0x36,0x6B,0x4F,0x4F,0x59,0x73,0xDA,0xEE,0xDC,0xC3,0x6C,0xCD,0x69,0x86,0x75,0x0D,0xAB,0x59,0xA7,0x19,0xD6,0x2D,0xB4,0x6E,0x9D,0x76,0x38,0x77,0x97,0xBA,0x7D,0xDA,0x6E,0x3D,0x5C,0xEA,0xCE,0x68,0x9B,0x8C,0x74,0xB2,0xD7,0xA5,0xAD,0x32,0xDA,0xD0,0x3F,0xA6,0x2E,0xCB,0x18,0xC5,0x7C,0xE9,0xBA,0xA4,0x72,0x98,0xEA,0x0E,0x42,0xA3,0xAF,0x62,0x0B,0x27,0xA5,0x98,0xB3,0x3D,0xC2,0x1D,0x0F,0x60,0xB6,0xB2,0x01,0xAC,0x18,0xBA,0xBA,0xE6,0x3C,0x4D,0x6B,0xF5,0xE9,0xBA,0xC9,0x0C,0xB5,0xB5,0xA7,0x6B,0x36,0x32,0xC4,0xD6,0xAD,0xBE,0xD9,0x4C,0xE7,0x58,0x93,0xFA,0xA2,0x27,0x98,0xB5,0x65,0xE8,0x8B,0x18,0x47,0xD2,0xBC,0xAE,0x2F,0xB4,0x03,0xD9,0xF2,0x9A,0xBE,0xA0,0x4A,0xA4,0xEC,0x06,0x01,0xD8,0xAE,0x23,0x01,0xC7,0xB5,0xB7,0xAE,0xD9,0x54,0xF3,0xDC,0x74,0xBA,0xE6,0xC2,0x5D,0x6C,0xF3,0xE9,0xBA,0x8B,0x08,0xD1,0x2D,0xA3,0xAF,0x2E,0xCD,0x34,0x3E,0xB9,0xBE,0x91,0x30,0x8B,0xA8,0x14,0xFA,0xC6,0x4C,0x5D,0x62,0x76,0xE9,0x9A,0x29,0x57,0xF1,0x85,0xAB,0x6B,0x2E,0xC2,0xC5,0x3E,0x9F,0xBE,0xB9,0x88,0x10,0xDD,0x52,0xFA,0xC6,0x2B,0x54,0xED,0x55,0xEA,0x1B,0x4B,0x67,0xCD,0x9B,0xA3,0x1B,0xC2,0x53,0x25,0x9F,0x9E,0x6E,0x68,0x0B,0x93,0x5C,0x7B,0xBA,0xE1,0xC2,0x4C,0xF2,0xF6,0x69,0x87,0x0F,0x35,0xCB,0x4B,0xA7,0x1B,0x3E,0x54,0xAD,0x2E,0x9F,0x6E,0xBA,0x10,0xB5,0xBA,0xBC,0xFA,0xE9,0x9D,0xC5,0xFA,0xF6,0x00,0x96,0x73,0x1A,0xC0,0xB4,0x46,0xA9,0x6F,0xD2,0x44,0xB9,0xE7,0xA6,0x61,0x20,0x53,0xD3,0x68,0x92,0x86,0xCA,0x53,0x48,0x6B,0xC9,0x18,0x9A,0x2F,0x53,0x93,0x3E,0x6B,0xE8,0x21,0xDD,0x8C,0xFB,0x9E,0xA1,0x87,0x70,0x33,0xEE,0xBB,0x86,0x16,0xD3,0xD5,0xA5,0xDF,0x18,0x6A,0x4C,0x13,0x97,0xBC,0x65,0xAC,0xAE,0x8C,0xC3,0xB4,0x93,0x81,0xEB,0xD5,0x70,0x9D,0x91,0x86,0x61,0x45,0x45,0x2D,0x49,0xEB,0x93,0x8A,0x4E,0xD7,0x38,0xA3,0x2F,0x2A,0x27,0x59,0xB3,0x9C,0xBE,0xE8,0xEE,0x74,0xD5,0x7A,0xFA,0xA2,0xAB,0x2B,0x44,0xCB,0x19,0x8A,0xAE,0xAE,0x54,0x2D,0x67,0x68,0x2A,0x2A,0x4B,0xD5,0x9E,0xA1,0xDB,0xC8,0x30,0x69,0x7B,0x86,0xE1,0xC2,0x43,0x64,0xCB,0x19,0xA6,0x4B,0x53,0xD5,0xCF,0x0B,0x98,0xD6,0x75,0x00,0xCB,0xB8,0x1E,0x60,0x1A,0xD7,0xD3,0x0F,0xEB,0x1A,0xD6,0x93,0x4E,0x3F,0xAC,0x6B,0x58,0xCD,0x3A,0xC3,0xB0,0xEE,0xA1,0x75,0x79,0x0C,0xCD,0xB8,0x9B,0xD6,0xA9,0x30,0x66,0xA1,0x9A,0x39,0x03,0xC3,0x98,0x85,0x6A,0xE6,0x0C,0x34,0x63,0x96,0xA2,0x99,0x33,0x10,0x1C,0xB0,0x5D,0x47,0x00,0x8E,0x6B,0x6F,0x63,0xF3,0x29,0x12,0xDE,0x77,0x8D,0x2D,0xA4,0xA9,0x4B,0xDF,0x35,0xB6,0x90,0xAE,0x2E,0x7D,0xC7,0x54,0x63,0xA9,0x84,0xE6,0x75,0x53,0x4D,0xC1,0xD2,0x91,0x97,0x00,0xDB,0x77,0x24,0x60,0xBB,0x8E,0x02,0x6C,0xDB,0xB6,0xC6,0x6E,0x5D,0x2D,0xF2,0xE1,0x19,0x86,0x0F,0x35,0xCB,0x5B,0x67,0x1C,0x3E,0xD4,0xAC,0x6E,0x9D,0x71,0xF8,0x50,0xB5,0xBA,0x7C,0xC6,0xE9,0x43,0xD4,0xFA,0xF2,0x02,0xA6,0x77,0x1E,0xC0,0xF2,0x4E,0x6D,0x9A,0xC6,0x58,0xAC,0x1E,0x85,0x29,0x0B,0xD5,0xCC,0x19,0x18,0xA6,0x2C,0x54,0x33,0x67,0x60,0x98,0xB2,0x10,0xCD,0x9C,0x81,0x69,0xCA,0x2A,0xCC,0x44,0xE3,0x87,0x39,0xDB,0x35,0x64,0xCD,0xB4,0xE6,0xE6,0x33,0x83,0x79,0xF5,0x99,0xBB,0x4F,0x77,0xD6,0x2D,0x63,0x6E,0x36,0x4D,0xC5,0x5E,0xB9,0x39,0x0B,0xD5,0xCC,0x19,0xE8,0x96,0x2C,0x44,0x33,0x67,0xA0,0x5A,0xB2,0x14,0x8D,0x9C,0x41,0xC0,0xF8,0xAE,0xCA,0xAD,0xCC,0x76,0xE0,0xA6,0x4D,0x8D,0xC8,0xD8,0x09,0x98,0xBE,0xCD,0x01,0x53,0x87,0x27,0xE0,0xF8,0xC8,0x04,0x1C,0x9B,0x99,0x80,0xEB,0x33,0x0B,0xB0,0x84,0x6A,0x1B,0x9B,0x10,0xCD,0xCE,0x1B,0x6B,0xEC,0x42,0x35,0x3A,0x67,0x1E,0x6C,0x08,0xD1,0xE8,0x5C,0xB8,0x96,0x21,0x45,0xA3,0xF3,0xE2,0xC2,0x86,0x54,0x8D,0xCA,0x9B,0x6B,0xEB,0x52,0x34,0x2A,0x2F,0x35,0xBC,0x0B,0xD1,0xE8,0x7C,0x50,0xCE,0x2E,0x4C,0x3D,0xA3,0x71,0x02,0x8E,0x9D,0x4C,0xC0,0x71,0x93,0x01,0x38,0xB6,0xC2,0x00,0xDB,0x77,0x24,0xE0,0xD8,0xF2,0x02,0x4C,0xD3,0x3A,0xF6,0xE6,0xC3,0xD4,0xE2,0xF5,0xD9,0xBB,0x4F,0x37,0xD6,0xCD,0xEB,0xE8,0x3E,0xDC,0x58,0xBF,0x8C,0xA3,0xB9,0x70,0x63,0x5B,0x9D,0xCE,0xA2,0x26,0x48,0x24,0x73,0x38,0x8B,0x18,0x47,0xD2,0xBC,0xEE,0x2C,0xAC,0x83,0x58,0xF3,0x99,0xB3,0xE0,0x4A,0xE4,0xE8,0x86,0xB0,0x82,0x2B,0x89,0xB2,0x1B,0xC0,0x03};
const uint8_t spHIT[] PROGMEM =  {0x20,0x80,0xEB,0x84,0x12,0x70,0x42,0x70,0x01,0x56,0x0C,0x5A,0xCB,0xF0,0x29,0xA6,0xD4,0xF7,0xCC,0xDD,0x85,0x99,0x62,0xBE,0x35,0x77,0x13,0xE6,0x86,0x7E,0xDB,0xD4,0x54,0xB8,0x2B,0xFA,0x0B,0xD0,0x30,0xE1,0x1E,0x2A,0xA7,0x00,0x3B,0x56,0x0C,0x60,0x85,0xF6,0x05,0x2C,0x5F,0xB1,0xA6,0xEE,0xC3,0xDD,0x7A,0xF4,0x99,0xBA,0xF7,0x08,0xAD,0x49,0x67,0xEA,0xDE,0xC3,0xA5,0x26,0xAF,0xA9,0x85,0x48,0x93,0xBA,0x52,0xA6,0xEA,0x32,0x4C,0xE2,0x8C,0x99,0xAA,0x71,0x56,0xB7,0x3A,0x66,0xEA,0xCC,0x4C,0x42,0xDB,0x28,0x60,0x9B,0xF0,0x00,0xEC,0x92,0x5A,0x80,0x5D,0x37,0x1B,0x70,0x52,0xF2,0x6A,0xBA,0x14,0xCD,0xAA,0x4B,0xA7,0xE9,0x42,0x34,0x2A,0x67,0x9D,0x79,0x08,0xD1,0xE8,0xBC,0x75,0xD2,0x21,0x54,0xA3,0x72,0xE6,0x69,0x87,0x14,0x89,0xCA,0x4B,0xA3,0xEB,0x42,0xC4,0x2B,0x1F,0x3A,0xBC,0x73,0xD1,0x98,0x78,0xC0,0xF8,0xAE,0xCA,0xAD,0xCC,0x76,0xE2,0xA6,0x0D,0x8D,0xC8,0xD8,0x05,0x98,0xBE,0xCD,0x41,0x43,0xA6,0x7A,0xA4,0x94,0xD0,0x77,0xE6,0x6A,0xE2,0xB3,0x43,0xDF,0xA8,0x5A,0xA8,0xCD,0x1E,0x7D,0x73,0x19,0x26,0xFE,0xEA,0xF4,0xDD,0x45,0x84,0xE8,0x96,0xD3,0x37,0x97,0xE1,0x62,0x9F,0x53,0xDF,0x6C,0xB9,0x78,0x6C,0x84,0x00,0x6C,0xD7,0x91,0x80,0xE3,0xCA,0x5B,0xDF,0x4C,0xBB,0x7B,0xB5,0x5E,0x43,0x75,0x95,0x21,0xB9,0xF8,0x8C,0xD5,0x54,0x95,0xD9,0xBA,0x33,0x56,0xDD,0x95,0x6E,0xEB,0xCE,0x54,0x75,0x57,0xBA,0xB5,0x3D,0x73,0x35,0x5D,0xE1,0xD6,0xF6,0x2C,0xD5,0x74,0x86,0x5B,0xD7,0xB3,0x54,0x5B,0x91,0x2E,0x7D,0xD7,0x5A,0x5C,0x7A,0x84,0xE5,0x1B,0x5B,0xB1,0xE9,0x16,0x9E,0x6D,0xEC,0xC5,0x96,0x6B,0x78,0xF6,0x76,0x14,0x5B,0xCE,0x19,0xDE,0xD3,0x51,0x92,0x31,0x4D,0x25,0x57,0x47,0x74,0xC2,0x51,0x19,0xAB,0x1C,0x33,0x06,0x6B,0xA8,0x9D,0x71,0x74,0xA7,0xA4,0x59,0x8D,0xD7,0x31,0x8C,0x8A,0x46,0x3E,0x1A,0xE7,0x30,0xA6,0xEA,0xF1,0x70,0x9C,0xC3,0x98,0xA8,0xE7,0xC3,0x74,0x76,0xAD,0x6A,0x91,0x37,0xC1,0x09,0x43,0xA5,0x45,0xBA,0xE3,0x04,0x4C,0xDF,0x96,0x80,0x69,0xCA,0x58,0xD9,0x75,0x8A,0x67,0x48,0x02,0x00,0x80,0x07};
const uint8_t spROOMS_TOO_BRIGHT[] PROGMEM = {0x2A,0xED,0x28,0xC3,0xB2,0x1C,0x87,0x34,0x99,0xD6,0xC8,0x88,0x1C,0x92,0x18,0x93,0x63,0xA4,0x8E,0x49,0xC2,0x60,0xE9,0x90,0x24,0x26,0x09,0xCD,0xD9,0xC2,0xE3,0x98,0x38,0x0C,0x63,0x2F,0x73,0x6C,0x82,0xB8,0xC9,0xC6,0xD4,0x59,0xF0,0xE2,0x24,0x2F,0x0B,0xFB,0xC5,0x4D,0x93,0xAC,0xDD,0xE3,0x36,0x3B,0x57,0xD5,0x4A,0x6B,0x3C,0xDA,0x1C,0xCD,0xC7,0xB4,0xCE,0x68,0x8A,0xF7,0x18,0xD5,0xB9,0xAD,0x29,0x3A,0x62,0x9C,0xEB,0x26,0x33,0x9B,0xA8,0x36,0x4C,0xEA,0xAC,0x11,0xCC,0x72,0xD0,0x72,0x00,0xA6,0xD5,0x0C,0xC0,0x94,0x1C,0x01,0xB8,0x4E,0xC2,0x01,0x3F,0x68,0x28,0xE0,0x77,0x17,0x04,0xFC,0x1B,0xAC,0x80,0x17,0x25,0x0A,0x70,0x8C,0x47,0xF1,0x9A,0x71,0xB5,0xD4,0x24,0xC9,0xCD,0x56,0x3C,0x3C,0xA6,0xA6,0x21,0x1A,0xE9,0xB0,0xA8,0x1B,0xDC,0x60,0x75,0xC5,0x33,0x8E,0xF3,0x7C,0xF0,0x61,0xCB,0xA8,0xC4,0xF7,0x2E,0xC3,0x55,0x2D,0x83,0x80,0xB2,0x48,0xB3,0x74,0xC7,0x21,0xCE,0x32,0xDC,0xC3,0x12,0xBB,0x28,0x56,0xE1,0x6C,0xB7,0xEB,0xC2,0x38,0x28,0xDB,0x2D,0x69,0x0A,0x62,0x97,0x4A,0x8F,0x24,0xC3,0xCF,0xC9,0x32,0x2D,0x9A,0x2E,0xBF,0x16,0xAD,0xD0,0x5A,0x36,0x82,0xD6,0xB5,0x4C,0xA7,0x5E,0x8B,0xDA,0x90,0x14,0xDF,0x78,0x25,0x6E,0x9D,0xC3,0x63,0xE2,0x85,0xA4,0x1F,0x31,0xF3,0x8E,0x63,0xD2,0x7E,0xC8,0x24,0xBA,0x0A,0xCA,0xFA,0x20,0x15,0xEB,0xDA,0x00,0x02,0x78,0xD1,0xAB,0x00,0xD7,0x44,0x16,0x60,0xC9,0xCA,0xE6,0x94,0xAE,0xDE,0xEA,0x8D,0x87,0x59,0x96,0x5B,0xAA,0x37,0x6D,0x5A,0xBD,0x12,0xE9,0xD1,0xA4,0x28,0xF5,0x71,0xB9,0x47,0xD4,0x24,0xD7,0x2F,0x19,0x6E,0x51,0x8D,0x5C,0x5F,0x84,0x16,0x47,0x6D,0x72,0x3B,0x5A,0x12,0x19,0x67,0xC9,0x6D,0x58,0xBB,0x64,0xD5,0x95,0xB7,0x1E,0x5D,0x6C,0x73,0x56,0x5E,0x7B,0x74,0x70,0xCC,0x5E,0x72,0xAB,0xD6,0x29,0x39,0x65,0x14,0xB5,0x5B,0x87,0x65,0x9C,0xA2,0x94,0xA1,0x6D,0x65,0x71,0x9A,0x5A,0x9A,0x96,0xA7,0x56,0x1D,0x6A,0x49,0x5E,0x1A,0x5E,0x67,0x94,0xC5,0xC7,0x98,0x65,0xDC,0xA1,0x16,0x53,0x6D,0x12,0x71,0x47,0x99,0xF5,0x94,0xB3,0xD7,0x1D,0x6A,0x32,0x5D,0x22,0x91,0x74,0xA8,0xD9,0x76,0x89,0x47,0x92,0xA5,0x66,0x5F,0x29,0x95,0x89,0x96,0x5A,0x4A,0x99,0x54,0x36,0x5A,0x6A,0x49,0xED,0xEA,0xB1,0xE5,0x94,0x35,0x45,0xB8,0xC7,0xE2,0xA3,0xB5,0x1E,0x61,0x16,0x6D,0x96,0xD1,0xB6,0x85,0x5A,0xD4,0x1E,0x66,0xDF,0x62,0xE2,0x95,0xA4,0x59,0xBD,0x0A,0x6B,0x65,0x6B,0xE6,0xF4,0xA1,0x28,0x16,0xA9,0x05,0xF0,0x47,0x86,0x03,0xBE,0xB7,0x08,0xC0,0x33,0x99,0x01,0xB8,0x3A,0x22,0x01,0x4F,0x65,0x04,0xE0,0x1B,0xCF,0x00,0x7C,0x6B,0x19,0x80,0x1F,0x2D,0x1D,0xF0,0xBB,0xA5,0x01,0x5E,0xF1,0x64,0xC0,0x32,0x11,0xF0};

const uint8_t spDUCK[] PROGMEM = {0x00, 0x80,0x98,0xD9,0xC4,0x38,0x3D,0xF6,0x08,0x87,0x51,0x0D,0x8B,0x24,0xA7,0xCC,0xC6,0x22,0x32,0x1A,0xAF,0x32,0x3A,0xEF,0xF0,0x6C,0x3C,0xAA,0x18,0x7D,0xC4,0x27,0xD1,0xA8,0x62,0xCE,0x76,0xDD,0xDA,0xAB,0x4C,0x3E,0x26,0xA5,0x1B,0xAD,0x3C,0xC5,0x8C,0x90,0x69,0x54,0xF2,0x94,0xDD,0xCC,0xBB,0xB4,0x4A,0x73,0x0E,0x30,0xB1,0xD8,0xC0,0xCA,0x5A,0xDD,0xD3,0x3D,0x6D,0xA8,0x6B,0x0D,0x2B,0xCB,0x34,0x4A,0xA8,0xB5,0xB9,0x33,0xEA,0x10,0xBE,0x0E,0xD3,0xB2,0x88,0x05,0xF0, 0x00};
const uint8_t spGOOSE[] PROGMEM = {0x00, 0x00, 0xC9,0x88,0xDA,0xB2,0x22,0x16,0x2D,0x23,0x5A,0xF7,0xA8,0x9C,0xB2,0xB4,0xE8,0x2D,0x3C,0xB3,0xEE,0xD1,0x62,0x70,0xB3,0x8E,0x3A,0x47,0x0B,0xAE,0x5C,0xC6,0x9B,0x2C,0x2D,0xF8,0x4C,0x2D,0x5B,0xBC,0x8C,0xE0,0x32,0xB5,0x74,0xF5,0x32,0x82,0xA9,0xE4,0xF6,0x36,0xCB,0x0C,0xA6,0x93,0xA6,0xE2,0x2C,0x2B,0x98,0x4E,0xEA,0x8A,0xB3,0xAC,0xA0,0xBA,0xA8,0xB3,0xF1,0xB2,0x83,0xEA,0xE2,0xCC,0xC6,0xCB,0x09,0xA2,0x4B,0xC3,0xDA,0x0C,0x37,0xA8,0xEC,0x48,0x6E,0x3D,0x3C,0x6F,0x3A,0xB5,0xAC,0x51,0xF3,0x9D,0x2B,0x97,0x8A,0x9A,0x25,0x32,0xA1,0x42,0x2B,0x2A,0x95,0xC4,0xA4,0x34,0xED,0xAA,0x59,0x32,0x17,0x42,0xAD,0xB3,0x76,0xC9,0xA3,0x0D,0x55,0xF7,0xD9,0xA9,0x2A,0x32,0x4C,0xD2,0x1A,0x37,0x60,0x1B,0xAF,0x02,0x5C,0xE7,0x55,0x80,0xA7,0x3C,0x12,0x70,0x65,0x5A,0x02,0x9E,0x0A,0x4D,0xC0,0x37,0xEA,0x01,0xF8,0xD1,0x33,0x00,0xD7,0x47,0x3A,0xE0,0xB8,0x48,0x07,0x0D,0x97,0x1D,0xEE,0x76,0x05,0x34,0xBC,0x87,0x86,0xC7,0x7E, 0x00};
