#ifndef READ_U_H_INCLUDED
#define READ_U_H_INCLUDED

/**
 * Reads an u8 from a file descriptor
 *
 * @param fd file descriptor
 * @param val where the value should be stored
 *
 * @return 0 on error, 1 otherwise
 */
int read_u8(int fd, u8 *val);


/**
 * Reads an u16 from a file descriptor
 *
 * @param fd file descriptor
 * @param val where the value should be stored
 *
 * @return 0 on error, 1 otherwise
 */
int read_u16(int fd, u16 *val);


/**
 * Reads an u32 from a file descriptor
 *
 * @param fd file descriptor
 * @param val where the value should be stored
 *
 * @return 0 on error, 1 otherwise
 */
int read_u32(int fd, u32 *val);


/**
 * Converts ID3 size
 *
 * @param size initial size
 *
 * @return the converted size (every 7th bit of each byte has been removed)
 */
u32 convert_size(u32 size);


#endif // READ_U_H_INCLUDED
