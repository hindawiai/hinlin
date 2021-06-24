<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* MFD cell driver data क्रम the DS1WM driver
 *
 * to be defined in the MFD device that is
 * using this driver क्रम one of his sub devices
 */

काष्ठा ds1wm_driver_data अणु
	पूर्णांक active_high;
	पूर्णांक घड़ी_rate;
	/* in milliseconds, the amount of समय to
	 * sleep following a reset pulse. Zero
	 * should work अगर your bus devices recover
	 * समय respects the 1-wire spec since the
	 * ds1wm implements the precise timings of
	 * a reset pulse/presence detect sequence.
	 */
	अचिन्हित पूर्णांक reset_recover_delay;

	/* Say 1 here क्रम big endian Hardware
	 * (only relevant with bus-shअगरt > 0
	 */
	bool is_hw_big_endian;

	/* left shअगरt of रेजिस्टर number to get रेजिस्टर address offsett.
	 * Only 0,1,2 allowed क्रम 8,16 or 32 bit bus width respectively
	 */
	अचिन्हित पूर्णांक bus_shअगरt;
पूर्ण;
