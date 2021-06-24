<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* speakup_acntpc.h - header file क्रम speakups Accent-PC driver. */

#घोषणा SYNTH_IO_EXTENT	0x02

#घोषणा SYNTH_CLEAR	0x18		/* stops speech */

	/* Port Status Flags */
#घोषणा SYNTH_READABLE	0x01	/* mask क्रम bit which is nonzero अगर a
				 * byte can be पढ़ो from the data port
				 */
#घोषणा SYNTH_WRITABLE	0x02	/* mask क्रम RDY bit, which when set to
				 * 1, indicates the data port is पढ़ोy
				 *  to accept a byte of data.
				 */
#घोषणा SYNTH_QUIET	'S' /* synth is not speaking */
#घोषणा SYNTH_FULL	'F' /* synth is full. */
#घोषणा SYNTH_ALMOST_EMPTY 'M' /* synth has less than 2 seconds of text left */
#घोषणा SYNTH_SPEAKING	's' /* synth is speaking and has a fare way to go */
