<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// LPC variant I/O क्रम Microchip EC
//
// Copyright (C) 2016 Google, Inc

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/mutex.h>
#समावेश <linux/types.h>

#समावेश "cros_ec_lpc_mec.h"

/*
 * This mutex must be held जबतक accessing the EMI unit. We can't rely on the
 * EC mutex because memmap data may be accessed without it being held.
 */
अटल DEFINE_MUTEX(io_mutex);
अटल u16 mec_emi_base, mec_emi_end;

/**
 * cros_ec_lpc_mec_emi_ग_लिखो_address() - Initialize EMI at a given address.
 *
 * @addr: Starting पढ़ो / ग_लिखो address
 * @access_type: Type of access, typically 32-bit स्वतः-increment
 */
अटल व्योम cros_ec_lpc_mec_emi_ग_लिखो_address(u16 addr,
			क्रमागत cros_ec_lpc_mec_emi_access_mode access_type)
अणु
	outb((addr & 0xfc) | access_type, MEC_EMI_EC_ADDRESS_B0(mec_emi_base));
	outb((addr >> 8) & 0x7f, MEC_EMI_EC_ADDRESS_B1(mec_emi_base));
पूर्ण

/**
 * cros_ec_lpc_mec_in_range() - Determine अगर addresses are in MEC EMI range.
 *
 * @offset: Address offset
 * @length: Number of bytes to check
 *
 * Return: 1 अगर in range, 0 अगर not, and -EINVAL on failure
 *         such as the mec range not being initialized
 */
पूर्णांक cros_ec_lpc_mec_in_range(अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक length)
अणु
	अगर (length == 0)
		वापस -EINVAL;

	अगर (WARN_ON(mec_emi_base == 0 || mec_emi_end == 0))
		वापस -EINVAL;

	अगर (offset >= mec_emi_base && offset < mec_emi_end) अणु
		अगर (WARN_ON(offset + length - 1 >= mec_emi_end))
			वापस -EINVAL;
		वापस 1;
	पूर्ण

	अगर (WARN_ON(offset + length > mec_emi_base && offset < mec_emi_end))
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * cros_ec_lpc_io_bytes_mec() - Read / ग_लिखो bytes to MEC EMI port.
 *
 * @io_type: MEC_IO_READ or MEC_IO_WRITE, depending on request
 * @offset:  Base पढ़ो / ग_लिखो address
 * @length:  Number of bytes to पढ़ो / ग_लिखो
 * @buf:     Destination / source buffer
 *
 * Return: 8-bit checksum of all bytes पढ़ो / written
 */
u8 cros_ec_lpc_io_bytes_mec(क्रमागत cros_ec_lpc_mec_io_type io_type,
			    अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक length,
			    u8 *buf)
अणु
	पूर्णांक i = 0;
	पूर्णांक io_addr;
	u8 sum = 0;
	क्रमागत cros_ec_lpc_mec_emi_access_mode access, new_access;

	/* Return checksum of 0 अगर winकरोw is not initialized */
	WARN_ON(mec_emi_base == 0 || mec_emi_end == 0);
	अगर (mec_emi_base == 0 || mec_emi_end == 0)
		वापस 0;

	/*
	 * Long access cannot be used on misaligned data since पढ़ोing B0 loads
	 * the data रेजिस्टर and writing B3 flushes.
	 */
	अगर (offset & 0x3 || length < 4)
		access = ACCESS_TYPE_BYTE;
	अन्यथा
		access = ACCESS_TYPE_LONG_AUTO_INCREMENT;

	mutex_lock(&io_mutex);

	/* Initialize I/O at desired address */
	cros_ec_lpc_mec_emi_ग_लिखो_address(offset, access);

	/* Skip bytes in हाल of misaligned offset */
	io_addr = MEC_EMI_EC_DATA_B0(mec_emi_base) + (offset & 0x3);
	जबतक (i < length) अणु
		जबतक (io_addr <= MEC_EMI_EC_DATA_B3(mec_emi_base)) अणु
			अगर (io_type == MEC_IO_READ)
				buf[i] = inb(io_addr++);
			अन्यथा
				outb(buf[i], io_addr++);

			sum += buf[i++];
			offset++;

			/* Extra bounds check in हाल of misaligned length */
			अगर (i == length)
				जाओ करोne;
		पूर्ण

		/*
		 * Use दीर्घ स्वतः-increment access except क्रम misaligned ग_लिखो,
		 * since writing B3 triggers the flush.
		 */
		अगर (length - i < 4 && io_type == MEC_IO_WRITE)
			new_access = ACCESS_TYPE_BYTE;
		अन्यथा
			new_access = ACCESS_TYPE_LONG_AUTO_INCREMENT;

		अगर (new_access != access ||
		    access != ACCESS_TYPE_LONG_AUTO_INCREMENT) अणु
			access = new_access;
			cros_ec_lpc_mec_emi_ग_लिखो_address(offset, access);
		पूर्ण

		/* Access [B0, B3] on each loop pass */
		io_addr = MEC_EMI_EC_DATA_B0(mec_emi_base);
	पूर्ण

करोne:
	mutex_unlock(&io_mutex);

	वापस sum;
पूर्ण
EXPORT_SYMBOL(cros_ec_lpc_io_bytes_mec);

व्योम cros_ec_lpc_mec_init(अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक end)
अणु
	mec_emi_base = base;
	mec_emi_end = end;
पूर्ण
EXPORT_SYMBOL(cros_ec_lpc_mec_init);

व्योम cros_ec_lpc_mec_destroy(व्योम)
अणु
	mutex_destroy(&io_mutex);
पूर्ण
EXPORT_SYMBOL(cros_ec_lpc_mec_destroy);
