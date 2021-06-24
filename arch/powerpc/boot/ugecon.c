<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/घातerpc/boot/ugecon.c
 *
 * USB Gecko bootwrapper console.
 * Copyright (C) 2008-2009 The GameCube Linux Team
 * Copyright (C) 2008,2009 Albert Herranz
 */

#समावेश <मानकघोष.स>
#समावेश "stdio.h"
#समावेश "types.h"
#समावेश "io.h"
#समावेश "ops.h"


#घोषणा EXI_CLK_32MHZ           5

#घोषणा EXI_CSR                 0x00
#घोषणा   EXI_CSR_CLKMASK       (0x7<<4)
#घोषणा     EXI_CSR_CLK_32MHZ   (EXI_CLK_32MHZ<<4)
#घोषणा   EXI_CSR_CSMASK        (0x7<<7)
#घोषणा     EXI_CSR_CS_0        (0x1<<7)  /* Chip Select 001 */

#घोषणा EXI_CR                  0x0c
#घोषणा   EXI_CR_TSTART         (1<<0)
#घोषणा   EXI_CR_WRITE		(1<<2)
#घोषणा   EXI_CR_READ_WRITE     (2<<2)
#घोषणा   EXI_CR_TLEN(len)      (((len)-1)<<4)

#घोषणा EXI_DATA                0x10


/* भव address base क्रम input/output, retrieved from device tree */
अटल व्योम *ug_io_base;


अटल u32 ug_io_transaction(u32 in)
अणु
	u32 *csr_reg = ug_io_base + EXI_CSR;
	u32 *data_reg = ug_io_base + EXI_DATA;
	u32 *cr_reg = ug_io_base + EXI_CR;
	u32 csr, data, cr;

	/* select */
	csr = EXI_CSR_CLK_32MHZ | EXI_CSR_CS_0;
	out_be32(csr_reg, csr);

	/* पढ़ो/ग_लिखो */
	data = in;
	out_be32(data_reg, data);
	cr = EXI_CR_TLEN(2) | EXI_CR_READ_WRITE | EXI_CR_TSTART;
	out_be32(cr_reg, cr);

	जबतक (in_be32(cr_reg) & EXI_CR_TSTART)
		barrier();

	/* deselect */
	out_be32(csr_reg, 0);

	data = in_be32(data_reg);
	वापस data;
पूर्ण

अटल पूर्णांक ug_is_txfअगरo_पढ़ोy(व्योम)
अणु
	वापस ug_io_transaction(0xc0000000) & 0x04000000;
पूर्ण

अटल व्योम ug_raw_अ_दो(अक्षर ch)
अणु
	ug_io_transaction(0xb0000000 | (ch << 20));
पूर्ण

अटल व्योम ug_अ_दो(अक्षर ch)
अणु
	पूर्णांक count = 16;

	अगर (!ug_io_base)
		वापस;

	जबतक (!ug_is_txfअगरo_पढ़ोy() && count--)
		barrier();
	अगर (count >= 0)
		ug_raw_अ_दो(ch);
पूर्ण

व्योम ug_console_ग_लिखो(स्थिर अक्षर *buf, पूर्णांक len)
अणु
	अक्षर *b = (अक्षर *)buf;

	जबतक (len--) अणु
		अगर (*b == '\n')
			ug_अ_दो('\r');
		ug_अ_दो(*b++);
	पूर्ण
पूर्ण

अटल पूर्णांक ug_is_adapter_present(व्योम)
अणु
	अगर (!ug_io_base)
		वापस 0;
	वापस ug_io_transaction(0x90000000) == 0x04700000;
पूर्ण

अटल व्योम *ug_grab_exi_io_base(व्योम)
अणु
	u32 v;
	व्योम *devp;

	devp = find_node_by_compatible(शून्य, "nintendo,flipper-exi");
	अगर (devp == शून्य)
		जाओ err_out;
	अगर (getprop(devp, "virtual-reg", &v, माप(v)) != माप(v))
		जाओ err_out;

	वापस (व्योम *)v;

err_out:
	वापस शून्य;
पूर्ण

व्योम *ug_probe(व्योम)
अणु
	व्योम *exi_io_base;
	पूर्णांक i;

	exi_io_base = ug_grab_exi_io_base();
	अगर (!exi_io_base)
		वापस शून्य;

	/* look क्रम a usbgecko on memcard slots A and B */
	क्रम (i = 0; i < 2; i++) अणु
		ug_io_base = exi_io_base + 0x14 * i;
		अगर (ug_is_adapter_present())
			अवरोध;
	पूर्ण
	अगर (i == 2)
		ug_io_base = शून्य;
	वापस ug_io_base;
पूर्ण

