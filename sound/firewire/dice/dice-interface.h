<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित SOUND_FIREWIRE_DICE_INTERFACE_H_INCLUDED
#घोषणा SOUND_FIREWIRE_DICE_INTERFACE_H_INCLUDED

/*
 * DICE device पूर्णांकerface definitions
 */

/*
 * Generally, all रेजिस्टरs can be पढ़ो like memory, i.e., with quadlet पढ़ो or
 * block पढ़ो transactions with at least quadlet-aligned offset and length.
 * Writes are not allowed except where noted; quadlet-sized रेजिस्टरs must be
 * written with a quadlet ग_लिखो transaction.
 *
 * All values are in big endian.  The DICE firmware runs on a little-endian CPU
 * and just byte-swaps _all_ quadlets on the bus, so values without endianness
 * (e.g. strings) get scrambled and must be byte-swapped again by the driver.
 */

/*
 * Streaming is handled by the "DICE driver" पूर्णांकerface.  Its रेजिस्टरs are
 * located in this निजी address space.
 */
#घोषणा DICE_PRIVATE_SPACE		0xffffe0000000uLL

/*
 * The रेजिस्टरs are organized in several sections, which are organized
 * separately to allow them to be extended inभागidually.  Whether a रेजिस्टर is
 * supported can be detected by checking its offset against its section's size.
 *
 * The section offset values are relative to DICE_PRIVATE_SPACE; the offset/
 * size values are measured in quadlets.  Read-only.
 */
#घोषणा DICE_GLOBAL_OFFSET		0x00
#घोषणा DICE_GLOBAL_SIZE		0x04
#घोषणा DICE_TX_OFFSET			0x08
#घोषणा DICE_TX_SIZE			0x0c
#घोषणा DICE_RX_OFFSET			0x10
#घोषणा DICE_RX_SIZE			0x14
#घोषणा DICE_EXT_SYNC_OFFSET		0x18
#घोषणा DICE_EXT_SYNC_SIZE		0x1c
#घोषणा DICE_UNUSED2_OFFSET		0x20
#घोषणा DICE_UNUSED2_SIZE		0x24

/*
 * Global settings.
 */

/*
 * Stores the full 64-bit address (node ID and offset in the node's address
 * space) where the device will send notअगरications.  Must be changed with
 * a compare/swap transaction by the owner.  This रेजिस्टर is स्वतःmatically
 * cleared on a bus reset.
 */
#घोषणा GLOBAL_OWNER			0x000
#घोषणा  OWNER_NO_OWNER			0xffff000000000000uLL
#घोषणा  OWNER_NODE_SHIFT		48

/*
 * A biपंचांगask with asynchronous events; पढ़ो-only.  When any event(s) happen,
 * the bits of previous events are cleared, and the value of this रेजिस्टर is
 * also written to the address stored in the owner रेजिस्टर.
 */
#घोषणा GLOBAL_NOTIFICATION		0x008
/* Some रेजिस्टरs in the Rx/Tx sections may have changed. */
#घोषणा  NOTIFY_RX_CFG_CHG		0x00000001
#घोषणा  NOTIFY_TX_CFG_CHG		0x00000002
/* Lock status of the current घड़ी source may have changed. */
#घोषणा  NOTIFY_LOCK_CHG		0x00000010
/* Write to the घड़ी select रेजिस्टर has been finished. */
#घोषणा  NOTIFY_CLOCK_ACCEPTED		0x00000020
/* Lock status of some घड़ी source has changed. */
#घोषणा  NOTIFY_EXT_STATUS		0x00000040
/* Other bits may be used क्रम device-specअगरic events. */

/*
 * A name that can be customized क्रम each device; पढ़ो/ग_लिखो.  Padded with zero
 * bytes.  Quadlets are byte-swapped.  The encoding is whatever the host driver
 * happens to be using.
 */
#घोषणा GLOBAL_NICK_NAME		0x00c
#घोषणा  NICK_NAME_SIZE			64

/*
 * The current sample rate and घड़ी source; पढ़ो/ग_लिखो.  Whether a घड़ी
 * source or sample rate is supported is device-specअगरic; the पूर्णांकernal घड़ी
 * source is always available.  Low/mid/high = up to 48/96/192 kHz.  This
 * रेजिस्टर can be changed even जबतक streams are running.
 */
#घोषणा GLOBAL_CLOCK_SELECT		0x04c
#घोषणा  CLOCK_SOURCE_MASK		0x000000ff
#घोषणा  CLOCK_SOURCE_AES1		0x00000000
#घोषणा  CLOCK_SOURCE_AES2		0x00000001
#घोषणा  CLOCK_SOURCE_AES3		0x00000002
#घोषणा  CLOCK_SOURCE_AES4		0x00000003
#घोषणा  CLOCK_SOURCE_AES_ANY		0x00000004
#घोषणा  CLOCK_SOURCE_ADAT		0x00000005
#घोषणा  CLOCK_SOURCE_TDIF		0x00000006
#घोषणा  CLOCK_SOURCE_WC		0x00000007
#घोषणा  CLOCK_SOURCE_ARX1		0x00000008
#घोषणा  CLOCK_SOURCE_ARX2		0x00000009
#घोषणा  CLOCK_SOURCE_ARX3		0x0000000a
#घोषणा  CLOCK_SOURCE_ARX4		0x0000000b
#घोषणा  CLOCK_SOURCE_INTERNAL		0x0000000c
#घोषणा  CLOCK_RATE_MASK		0x0000ff00
#घोषणा  CLOCK_RATE_32000		0x00000000
#घोषणा  CLOCK_RATE_44100		0x00000100
#घोषणा  CLOCK_RATE_48000		0x00000200
#घोषणा  CLOCK_RATE_88200		0x00000300
#घोषणा  CLOCK_RATE_96000		0x00000400
#घोषणा  CLOCK_RATE_176400		0x00000500
#घोषणा  CLOCK_RATE_192000		0x00000600
#घोषणा  CLOCK_RATE_ANY_LOW		0x00000700
#घोषणा  CLOCK_RATE_ANY_MID		0x00000800
#घोषणा  CLOCK_RATE_ANY_HIGH		0x00000900
#घोषणा  CLOCK_RATE_NONE		0x00000a00
#घोषणा  CLOCK_RATE_SHIFT		8

/*
 * Enable streaming; पढ़ो/ग_लिखो.  Writing a non-zero value (re)starts all
 * streams that have a valid iso channel set; zero stops all streams.  The
 * streams' parameters must be configured beक्रमe starting.  This रेजिस्टर is
 * स्वतःmatically cleared on a bus reset.
 */
#घोषणा GLOBAL_ENABLE			0x050

/*
 * Status of the sample घड़ी; पढ़ो-only.
 */
#घोषणा GLOBAL_STATUS			0x054
/* The current घड़ी source is locked. */
#घोषणा  STATUS_SOURCE_LOCKED		0x00000001
/* The actual sample rate; CLOCK_RATE_32000-_192000 or _NONE. */
#घोषणा  STATUS_NOMINAL_RATE_MASK	0x0000ff00

/*
 * Status of all घड़ी sources; पढ़ो-only.
 */
#घोषणा GLOBAL_EXTENDED_STATUS		0x058
/*
 * The _LOCKED bits always show the current status; any change generates
 * a notअगरication.
 */
#घोषणा  EXT_STATUS_AES1_LOCKED		0x00000001
#घोषणा  EXT_STATUS_AES2_LOCKED		0x00000002
#घोषणा  EXT_STATUS_AES3_LOCKED		0x00000004
#घोषणा  EXT_STATUS_AES4_LOCKED		0x00000008
#घोषणा  EXT_STATUS_ADAT_LOCKED		0x00000010
#घोषणा  EXT_STATUS_TDIF_LOCKED		0x00000020
#घोषणा  EXT_STATUS_ARX1_LOCKED		0x00000040
#घोषणा  EXT_STATUS_ARX2_LOCKED		0x00000080
#घोषणा  EXT_STATUS_ARX3_LOCKED		0x00000100
#घोषणा  EXT_STATUS_ARX4_LOCKED		0x00000200
#घोषणा  EXT_STATUS_WC_LOCKED		0x00000400
/*
 * The _SLIP bits करो not generate notअगरications; a set bit indicates that an
 * error occurred since the last समय when this रेजिस्टर was पढ़ो with
 * a quadlet पढ़ो transaction.
 */
#घोषणा  EXT_STATUS_AES1_SLIP		0x00010000
#घोषणा  EXT_STATUS_AES2_SLIP		0x00020000
#घोषणा  EXT_STATUS_AES3_SLIP		0x00040000
#घोषणा  EXT_STATUS_AES4_SLIP		0x00080000
#घोषणा  EXT_STATUS_ADAT_SLIP		0x00100000
#घोषणा  EXT_STATUS_TDIF_SLIP		0x00200000
#घोषणा  EXT_STATUS_ARX1_SLIP		0x00400000
#घोषणा  EXT_STATUS_ARX2_SLIP		0x00800000
#घोषणा  EXT_STATUS_ARX3_SLIP		0x01000000
#घोषणा  EXT_STATUS_ARX4_SLIP		0x02000000
#घोषणा  EXT_STATUS_WC_SLIP		0x04000000

/*
 * The measured rate of the current घड़ी source, in Hz; पढ़ो-only.
 */
#घोषणा GLOBAL_SAMPLE_RATE		0x05c

/*
 * Some old firmware versions करो not have the following global रेजिस्टरs.
 * Winकरोws drivers produced by TCAT lost backward compatibility in its
 * early release because they can handle firmware only which supports the
 * following रेजिस्टरs.
 */

/*
 * The version of the DICE driver specअगरication that this device conक्रमms to;
 * पढ़ो-only.
 */
#घोषणा GLOBAL_VERSION			0x060

/*
 * Supported sample rates and घड़ी sources; पढ़ो-only.
 */
#घोषणा GLOBAL_CLOCK_CAPABILITIES	0x064
#घोषणा  CLOCK_CAP_RATE_32000		0x00000001
#घोषणा  CLOCK_CAP_RATE_44100		0x00000002
#घोषणा  CLOCK_CAP_RATE_48000		0x00000004
#घोषणा  CLOCK_CAP_RATE_88200		0x00000008
#घोषणा  CLOCK_CAP_RATE_96000		0x00000010
#घोषणा  CLOCK_CAP_RATE_176400		0x00000020
#घोषणा  CLOCK_CAP_RATE_192000		0x00000040
#घोषणा  CLOCK_CAP_SOURCE_AES1		0x00010000
#घोषणा  CLOCK_CAP_SOURCE_AES2		0x00020000
#घोषणा  CLOCK_CAP_SOURCE_AES3		0x00040000
#घोषणा  CLOCK_CAP_SOURCE_AES4		0x00080000
#घोषणा  CLOCK_CAP_SOURCE_AES_ANY	0x00100000
#घोषणा  CLOCK_CAP_SOURCE_ADAT		0x00200000
#घोषणा  CLOCK_CAP_SOURCE_TDIF		0x00400000
#घोषणा  CLOCK_CAP_SOURCE_WC		0x00800000
#घोषणा  CLOCK_CAP_SOURCE_ARX1		0x01000000
#घोषणा  CLOCK_CAP_SOURCE_ARX2		0x02000000
#घोषणा  CLOCK_CAP_SOURCE_ARX3		0x04000000
#घोषणा  CLOCK_CAP_SOURCE_ARX4		0x08000000
#घोषणा  CLOCK_CAP_SOURCE_INTERNAL	0x10000000

/*
 * Names of all घड़ी sources; पढ़ो-only.  Quadlets are byte-swapped.  Names
 * are separated with one backslash, the list is terminated with two
 * backslashes.  Unused घड़ी sources are included.
 */
#घोषणा GLOBAL_CLOCK_SOURCE_NAMES	0x068
#घोषणा  CLOCK_SOURCE_NAMES_SIZE	256

/*
 * Capture stream settings.  This section includes the number/size रेजिस्टरs
 * and the रेजिस्टरs of all streams.
 */

/*
 * The number of supported capture streams; पढ़ो-only.
 */
#घोषणा TX_NUMBER			0x000

/*
 * The size of one stream's रेजिस्टर block, in quadlets; पढ़ो-only.  The
 * रेजिस्टरs of the first stream follow immediately afterwards; the रेजिस्टरs
 * of the following streams are offset by this रेजिस्टर's value.
 */
#घोषणा TX_SIZE				0x004

/*
 * The isochronous channel number on which packets are sent, or -1 अगर the
 * stream is not to be used; पढ़ो/ग_लिखो.
 */
#घोषणा TX_ISOCHRONOUS			0x008

/*
 * The number of audio channels; पढ़ो-only.  There will be one quadlet per
 * channel; the first channel is the first quadlet in a data block.
 */
#घोषणा TX_NUMBER_AUDIO			0x00c

/*
 * The number of MIDI ports, 0-8; पढ़ो-only.  If > 0, there will be one
 * additional quadlet in each data block, following the audio quadlets.
 */
#घोषणा TX_NUMBER_MIDI			0x010

/*
 * The speed at which the packets are sent, SCODE_100-_400; पढ़ो/ग_लिखो.
 * SCODE_800 is only available in Dice III.
 */
#घोषणा TX_SPEED			0x014

/*
 * Names of all audio channels; पढ़ो-only.  Quadlets are byte-swapped.  Names
 * are separated with one backslash, the list is terminated with two
 * backslashes.
 */
#घोषणा TX_NAMES			0x018
#घोषणा  TX_NAMES_SIZE			256

/*
 * Audio IEC60958 capabilities; पढ़ो-only.  Biपंचांगask with one bit per audio
 * channel.
 */
#घोषणा TX_AC3_CAPABILITIES		0x118

/*
 * Send audio data with IEC60958 label; पढ़ो/ग_लिखो.  Biपंचांगask with one bit per
 * audio channel.  This रेजिस्टर can be changed even जबतक the stream is
 * running.
 */
#घोषणा TX_AC3_ENABLE			0x11c

/*
 * Playback stream settings.  This section includes the number/size रेजिस्टरs
 * and the रेजिस्टरs of all streams.
 */

/*
 * The number of supported playback streams; पढ़ो-only.
 */
#घोषणा RX_NUMBER			0x000

/*
 * The size of one stream's रेजिस्टर block, in quadlets; पढ़ो-only.  The
 * रेजिस्टरs of the first stream follow immediately afterwards; the रेजिस्टरs
 * of the following streams are offset by this रेजिस्टर's value.
 */
#घोषणा RX_SIZE				0x004

/*
 * The isochronous channel number on which packets are received, or -1 अगर the
 * stream is not to be used; पढ़ो/ग_लिखो.
 */
#घोषणा RX_ISOCHRONOUS			0x008

/*
 * Index of first quadlet to be पूर्णांकerpreted; पढ़ो/ग_लिखो.  If > 0, that many
 * quadlets at the beginning of each data block will be ignored, and all the
 * audio and MIDI quadlets will follow.
 */
#घोषणा RX_SEQ_START			0x00c

/*
 * The number of audio channels; पढ़ो-only.  There will be one quadlet per
 * channel.
 */
#घोषणा RX_NUMBER_AUDIO			0x010

/*
 * The number of MIDI ports, 0-8; पढ़ो-only.  If > 0, there will be one
 * additional quadlet in each data block, following the audio quadlets.
 */
#घोषणा RX_NUMBER_MIDI			0x014

/*
 * Names of all audio channels; पढ़ो-only.  Quadlets are byte-swapped.  Names
 * are separated with one backslash, the list is terminated with two
 * backslashes.
 */
#घोषणा RX_NAMES			0x018
#घोषणा  RX_NAMES_SIZE			256

/*
 * Audio IEC60958 capabilities; पढ़ो-only.  Biपंचांगask with one bit per audio
 * channel.
 */
#घोषणा RX_AC3_CAPABILITIES		0x118

/*
 * Receive audio data with IEC60958 label; पढ़ो/ग_लिखो.  Biपंचांगask with one bit
 * per audio channel.  This रेजिस्टर can be changed even जबतक the stream is
 * running.
 */
#घोषणा RX_AC3_ENABLE			0x11c

/*
 * Extended synchronization inक्रमmation.
 * This section can be पढ़ो completely with a block पढ़ो request.
 */

/*
 * Current घड़ी source; पढ़ो-only.
 */
#घोषणा EXT_SYNC_CLOCK_SOURCE		0x000

/*
 * Clock source is locked (boolean); पढ़ो-only.
 */
#घोषणा EXT_SYNC_LOCKED			0x004

/*
 * Current sample rate (CLOCK_RATE_* >> CLOCK_RATE_SHIFT), _32000-_192000 or
 * _NONE; पढ़ो-only.
 */
#घोषणा EXT_SYNC_RATE			0x008

/*
 * ADAT user data bits; पढ़ो-only.
 */
#घोषणा EXT_SYNC_ADAT_USER_DATA		0x00c
/* The data bits, अगर available. */
#घोषणा  ADAT_USER_DATA_MASK		0x0f
/* The data bits are not available. */
#घोषणा  ADAT_USER_DATA_NO_DATA		0x10

#पूर्ण_अगर
