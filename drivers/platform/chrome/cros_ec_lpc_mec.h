<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * LPC variant I/O क्रम Microchip EC
 *
 * Copyright (C) 2016 Google, Inc
 */

#अगर_अघोषित __CROS_EC_LPC_MEC_H
#घोषणा __CROS_EC_LPC_MEC_H

क्रमागत cros_ec_lpc_mec_emi_access_mode अणु
	/* 8-bit access */
	ACCESS_TYPE_BYTE = 0x0,
	/* 16-bit access */
	ACCESS_TYPE_WORD = 0x1,
	/* 32-bit access */
	ACCESS_TYPE_LONG = 0x2,
	/*
	 * 32-bit access, पढ़ो or ग_लिखो of MEC_EMI_EC_DATA_B3 causes the
	 * EC data रेजिस्टर to be incremented.
	 */
	ACCESS_TYPE_LONG_AUTO_INCREMENT = 0x3,
पूर्ण;

क्रमागत cros_ec_lpc_mec_io_type अणु
	MEC_IO_READ,
	MEC_IO_WRITE,
पूर्ण;

/* EMI रेजिस्टरs are relative to base */
#घोषणा MEC_EMI_HOST_TO_EC(MEC_EMI_BASE)	((MEC_EMI_BASE) + 0)
#घोषणा MEC_EMI_EC_TO_HOST(MEC_EMI_BASE)	((MEC_EMI_BASE) + 1)
#घोषणा MEC_EMI_EC_ADDRESS_B0(MEC_EMI_BASE)	((MEC_EMI_BASE) + 2)
#घोषणा MEC_EMI_EC_ADDRESS_B1(MEC_EMI_BASE)	((MEC_EMI_BASE) + 3)
#घोषणा MEC_EMI_EC_DATA_B0(MEC_EMI_BASE)	((MEC_EMI_BASE) + 4)
#घोषणा MEC_EMI_EC_DATA_B1(MEC_EMI_BASE)	((MEC_EMI_BASE) + 5)
#घोषणा MEC_EMI_EC_DATA_B2(MEC_EMI_BASE)	((MEC_EMI_BASE) + 6)
#घोषणा MEC_EMI_EC_DATA_B3(MEC_EMI_BASE)	((MEC_EMI_BASE) + 7)

/**
 * cros_ec_lpc_mec_init() - Initialize MEC I/O.
 *
 * @base: MEC EMI Base address
 * @end: MEC EMI End address
 */
व्योम cros_ec_lpc_mec_init(अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक end);

/*
 * cros_ec_lpc_mec_destroy
 *
 * Cleanup MEC I/O.
 */
व्योम cros_ec_lpc_mec_destroy(व्योम);

/**
 * cros_ec_lpc_mec_in_range() - Determine अगर addresses are in MEC EMI range.
 *
 * @offset: Address offset
 * @length: Number of bytes to check
 *
 * Return: 1 अगर in range, 0 अगर not, and -EINVAL on failure
 *         such as the mec range not being initialized
 */
पूर्णांक cros_ec_lpc_mec_in_range(अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक length);

/**
 * cros_ec_lpc_io_bytes_mec - Read / ग_लिखो bytes to MEC EMI port
 *
 * @io_type: MEC_IO_READ or MEC_IO_WRITE, depending on request
 * @offset:  Base पढ़ो / ग_लिखो address
 * @length:  Number of bytes to पढ़ो / ग_लिखो
 * @buf:     Destination / source buffer
 *
 * @वापस 8-bit checksum of all bytes पढ़ो / written
 */
u8 cros_ec_lpc_io_bytes_mec(क्रमागत cros_ec_lpc_mec_io_type io_type,
			    अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक length, u8 *buf);

#पूर्ण_अगर /* __CROS_EC_LPC_MEC_H */
