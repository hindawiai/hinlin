<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __842_H__
#घोषणा __842_H__

/* The 842 compressed क्रमmat is made up of multiple blocks, each of
 * which have the क्रमmat:
 *
 * <ढाँचा>[arg1][arg2][arg3][arg4]
 *
 * where there are between 0 and 4 ढाँचा args, depending on the specअगरic
 * ढाँचा operation.  For normal operations, each arg is either a specअगरic
 * number of data bytes to add to the output buffer, or an index poपूर्णांकing
 * to a previously-written number of data bytes to copy to the output buffer.
 *
 * The ढाँचा code is a 5-bit value.  This code indicates what to करो with
 * the following data.  Template codes from 0 to 0x19 should use the ढाँचा
 * table, the अटल "decomp_ops" table used in decompress.  For each ढाँचा
 * (table row), there are between 1 and 4 actions; each action corresponds to
 * an arg following the ढाँचा code bits.  Each action is either a "data"
 * type action, or a "index" type action, and each action results in 2, 4, or 8
 * bytes being written to the output buffer.  Each ढाँचा (i.e. all actions
 * in the table row) will add up to 8 bytes being written to the output buffer.
 * Any row with less than 4 actions is padded with noop actions, indicated by
 * N0 (क्रम which there is no corresponding arg in the compressed data buffer).
 *
 * "Data" actions, indicated in the table by D2, D4, and D8, mean that the
 * corresponding arg is 2, 4, or 8 bytes, respectively, in the compressed data
 * buffer should be copied directly to the output buffer.
 *
 * "Index" actions, indicated in the table by I2, I4, and I8, mean the
 * corresponding arg is an index parameter that poपूर्णांकs to, respectively, a 2,
 * 4, or 8 byte value alपढ़ोy in the output buffer, that should be copied to
 * the end of the output buffer.  Essentially, the index poपूर्णांकs to a position
 * in a ring buffer that contains the last N bytes of output buffer data.
 * The number of bits क्रम each index's arg are: 8 bits क्रम I2, 9 bits क्रम I4,
 * and 8 bits क्रम I8.  Since each index poपूर्णांकs to a 2, 4, or 8 byte section,
 * this means that I2 can reference 512 bytes ((2^8 bits = 256) * 2 bytes), I4
 * can reference 2048 bytes ((2^9 = 512) * 4 bytes), and I8 can reference 2048
 * bytes ((2^8 = 256) * 8 bytes).  Think of it as a kind-of ring buffer क्रम
 * each of I2, I4, and I8 that are updated क्रम each byte written to the output
 * buffer.  In this implementation, the output buffer is directly used क्रम each
 * index; there is no additional memory required.  Note that the index is पूर्णांकo
 * a ring buffer, not a sliding winकरोw; क्रम example, अगर there have been 260
 * bytes written to the output buffer, an I2 index of 0 would index to byte 256
 * in the output buffer, जबतक an I2 index of 16 would index to byte 16 in the
 * output buffer.
 *
 * There are also 3 special ढाँचा codes; 0x1b क्रम "repeat", 0x1c क्रम
 * "zeros", and 0x1e क्रम "end".  The "repeat" operation is followed by a 6 bit
 * arg N indicating how many बार to repeat.  The last 8 bytes written to the
 * output buffer are written again to the output buffer, N + 1 बार.  The
 * "zeros" operation, which has no arg bits, ग_लिखोs 8 zeros to the output
 * buffer.  The "end" operation, which also has no arg bits, संकेतs the end
 * of the compressed data.  There may be some number of padding (करोn't care,
 * but usually 0) bits after the "end" operation bits, to fill the buffer
 * length to a specअगरic byte multiple (usually a multiple of 8, 16, or 32
 * bytes).
 *
 * This software implementation also uses one of the undefined ढाँचा values,
 * 0x1d as a special "short data" ढाँचा code, to represent less than 8 bytes
 * of uncompressed data.  It is followed by a 3 bit arg N indicating how many
 * data bytes will follow, and then N bytes of data, which should be copied to
 * the output buffer.  This allows the software 842 compressor to accept input
 * buffers that are not an exact multiple of 8 bytes दीर्घ.  However, those
 * compressed buffers containing this sw-only ढाँचा will be rejected by
 * the 842 hardware decompressor, and must be decompressed with this software
 * library.  The 842 software compression module includes a parameter to
 * disable using this sw-only "short data" ढाँचा, and instead simply
 * reject any input buffer that is not a multiple of 8 bytes दीर्घ.
 *
 * After all actions क्रम each operation code are processed, another ढाँचा
 * code is in the next 5 bits.  The decompression ends once the "end" ढाँचा
 * code is detected.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/crc32.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <linux/sw842.h>

/* special ढाँचाs */
#घोषणा OP_REPEAT	(0x1B)
#घोषणा OP_ZEROS	(0x1C)
#घोषणा OP_END		(0x1E)

/* sw only ढाँचा - this is not in the hw design; it's used only by this
 * software compressor and decompressor, to allow input buffers that aren't
 * a multiple of 8.
 */
#घोषणा OP_SHORT_DATA	(0x1D)

/* additional bits of each op param */
#घोषणा OP_BITS		(5)
#घोषणा REPEAT_BITS	(6)
#घोषणा SHORT_DATA_BITS	(3)
#घोषणा I2_BITS		(8)
#घोषणा I4_BITS		(9)
#घोषणा I8_BITS		(8)
#घोषणा CRC_BITS	(32)

#घोषणा REPEAT_BITS_MAX		(0x3f)
#घोषणा SHORT_DATA_BITS_MAX	(0x7)

/* Arbitrary values used to indicate action */
#घोषणा OP_ACTION	(0x70)
#घोषणा OP_ACTION_INDEX	(0x10)
#घोषणा OP_ACTION_DATA	(0x20)
#घोषणा OP_ACTION_NOOP	(0x40)
#घोषणा OP_AMOUNT	(0x0f)
#घोषणा OP_AMOUNT_0	(0x00)
#घोषणा OP_AMOUNT_2	(0x02)
#घोषणा OP_AMOUNT_4	(0x04)
#घोषणा OP_AMOUNT_8	(0x08)

#घोषणा D2		(OP_ACTION_DATA  | OP_AMOUNT_2)
#घोषणा D4		(OP_ACTION_DATA  | OP_AMOUNT_4)
#घोषणा D8		(OP_ACTION_DATA  | OP_AMOUNT_8)
#घोषणा I2		(OP_ACTION_INDEX | OP_AMOUNT_2)
#घोषणा I4		(OP_ACTION_INDEX | OP_AMOUNT_4)
#घोषणा I8		(OP_ACTION_INDEX | OP_AMOUNT_8)
#घोषणा N0		(OP_ACTION_NOOP  | OP_AMOUNT_0)

/* the max of the regular ढाँचाs - not including the special ढाँचाs */
#घोषणा OPS_MAX		(0x1a)

#पूर्ण_अगर
