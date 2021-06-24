<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PPC_BOOT_PLANETCORE_H_
#घोषणा _PPC_BOOT_PLANETCORE_H_

#समावेश "types.h"

#घोषणा PLANETCORE_KEY_BOARD_TYPE   "BO"
#घोषणा PLANETCORE_KEY_BOARD_REV    "BR"
#घोषणा PLANETCORE_KEY_MB_RAM       "D1"
#घोषणा PLANETCORE_KEY_MAC_ADDR     "EA"
#घोषणा PLANETCORE_KEY_FLASH_SPEED  "FS"
#घोषणा PLANETCORE_KEY_IP_ADDR      "IP"
#घोषणा PLANETCORE_KEY_KB_NVRAM     "NV"
#घोषणा PLANETCORE_KEY_PROCESSOR    "PR"
#घोषणा PLANETCORE_KEY_PROC_VARIANT "PV"
#घोषणा PLANETCORE_KEY_SERIAL_BAUD  "SB"
#घोषणा PLANETCORE_KEY_SERIAL_PORT  "SP"
#घोषणा PLANETCORE_KEY_SWITCH       "SW"
#घोषणा PLANETCORE_KEY_TEMP_OFFSET  "TC"
#घोषणा PLANETCORE_KEY_TARGET_IP    "TIP"
#घोषणा PLANETCORE_KEY_CRYSTAL_HZ   "XT"

/* Prepare the table क्रम processing, by turning all newlines
 * पूर्णांकo शून्य bytes.
 */
व्योम planetcore_prepare_table(अक्षर *table);

/* Return the value associated with a given key in text,
 * decimal, or hex क्रमmat.
 *
 * Returns zero/शून्य on failure, non-zero on success.
 */
स्थिर अक्षर *planetcore_get_key(स्थिर अक्षर *table, स्थिर अक्षर *key);
पूर्णांक planetcore_get_decimal(स्थिर अक्षर *table, स्थिर अक्षर *key, u64 *val);
पूर्णांक planetcore_get_hex(स्थिर अक्षर *table, स्थिर अक्षर *key, u64 *val);

/* Updates the device tree local-mac-address properties based
 * on the EA tag.
 */
व्योम planetcore_set_mac_addrs(स्थिर अक्षर *table);

/* Sets the linux,मानक_निकास-path in the /chosen node.  This requires the
 * linux,planetcore-label property in each serial node.
 */
व्योम planetcore_set_मानक_निकास_path(स्थिर अक्षर *table);

#पूर्ण_अगर
