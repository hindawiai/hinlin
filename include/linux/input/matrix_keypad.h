<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _MATRIX_KEYPAD_H
#घोषणा _MATRIX_KEYPAD_H

#समावेश <linux/types.h>
#समावेश <linux/input.h>
#समावेश <linux/of.h>

#घोषणा MATRIX_MAX_ROWS		32
#घोषणा MATRIX_MAX_COLS		32

#घोषणा KEY(row, col, val)	((((row) & (MATRIX_MAX_ROWS - 1)) << 24) |\
				 (((col) & (MATRIX_MAX_COLS - 1)) << 16) |\
				 ((val) & 0xffff))

#घोषणा KEY_ROW(k)		(((k) >> 24) & 0xff)
#घोषणा KEY_COL(k)		(((k) >> 16) & 0xff)
#घोषणा KEY_VAL(k)		((k) & 0xffff)

#घोषणा MATRIX_SCAN_CODE(row, col, row_shअगरt)	(((row) << (row_shअगरt)) + (col))

/**
 * काष्ठा matrix_keymap_data - keymap क्रम matrix keyboards
 * @keymap: poपूर्णांकer to array of uपूर्णांक32 values encoded with KEY() macro
 *	representing keymap
 * @keymap_size: number of entries (initialized) in this keymap
 *
 * This काष्ठाure is supposed to be used by platक्रमm code to supply
 * keymaps to drivers that implement matrix-like keypads/keyboards.
 */
काष्ठा matrix_keymap_data अणु
	स्थिर uपूर्णांक32_t *keymap;
	अचिन्हित पूर्णांक	keymap_size;
पूर्ण;

/**
 * काष्ठा matrix_keypad_platक्रमm_data - platक्रमm-dependent keypad data
 * @keymap_data: poपूर्णांकer to &matrix_keymap_data
 * @row_gpios: poपूर्णांकer to array of gpio numbers representing rows
 * @col_gpios: poपूर्णांकer to array of gpio numbers reporesenting colums
 * @num_row_gpios: actual number of row gpios used by device
 * @num_col_gpios: actual number of col gpios used by device
 * @col_scan_delay_us: delay, measured in microseconds, that is
 *	needed beक्रमe we can keypad after activating column gpio
 * @debounce_ms: debounce पूर्णांकerval in milliseconds
 * @clustered_irq: may be specअगरied अगर पूर्णांकerrupts of all row/column GPIOs
 *	are bundled to one single irq
 * @clustered_irq_flags: flags that are needed क्रम the clustered irq
 * @active_low: gpio polarity
 * @wakeup: controls whether the device should be set up as wakeup
 *	source
 * @no_स्वतःrepeat: disable key स्वतःrepeat
 * @drive_inactive_cols: drive inactive columns during scan, rather than
 *	making them inमाला_दो.
 *
 * This काष्ठाure represents platक्रमm-specअगरic data that use used by
 * matrix_keypad driver to perक्रमm proper initialization.
 */
काष्ठा matrix_keypad_platक्रमm_data अणु
	स्थिर काष्ठा matrix_keymap_data *keymap_data;

	स्थिर अचिन्हित पूर्णांक *row_gpios;
	स्थिर अचिन्हित पूर्णांक *col_gpios;

	अचिन्हित पूर्णांक	num_row_gpios;
	अचिन्हित पूर्णांक	num_col_gpios;

	अचिन्हित पूर्णांक	col_scan_delay_us;

	/* key debounce पूर्णांकerval in milli-second */
	अचिन्हित पूर्णांक	debounce_ms;

	अचिन्हित पूर्णांक	clustered_irq;
	अचिन्हित पूर्णांक	clustered_irq_flags;

	bool		active_low;
	bool		wakeup;
	bool		no_स्वतःrepeat;
	bool		drive_inactive_cols;
पूर्ण;

पूर्णांक matrix_keypad_build_keymap(स्थिर काष्ठा matrix_keymap_data *keymap_data,
			       स्थिर अक्षर *keymap_name,
			       अचिन्हित पूर्णांक rows, अचिन्हित पूर्णांक cols,
			       अचिन्हित लघु *keymap,
			       काष्ठा input_dev *input_dev);
पूर्णांक matrix_keypad_parse_properties(काष्ठा device *dev,
				   अचिन्हित पूर्णांक *rows, अचिन्हित पूर्णांक *cols);

#घोषणा matrix_keypad_parse_of_params matrix_keypad_parse_properties

#पूर्ण_अगर /* _MATRIX_KEYPAD_H */
