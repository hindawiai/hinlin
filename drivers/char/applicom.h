<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* $Id: applicom.h,v 1.2 1999/08/28 15:09:49 dwmw2 Exp $ */


#अगर_अघोषित __LINUX_APPLICOM_H__
#घोषणा __LINUX_APPLICOM_H__


#घोषणा DATA_TO_PC_READY      0x00
#घोषणा TIC_OWNER_TO_PC       0x01
#घोषणा NUMCARD_OWNER_TO_PC   0x02
#घोषणा TIC_DES_TO_PC         0x03
#घोषणा NUMCARD_DES_TO_PC     0x04
#घोषणा DATA_FROM_PC_READY    0x05
#घोषणा TIC_OWNER_FROM_PC     0x06
#घोषणा NUMCARD_OWNER_FROM_PC 0x07
#घोषणा TIC_DES_FROM_PC       0x08
#घोषणा NUMCARD_DES_FROM_PC   0x09
#घोषणा ACK_FROM_PC_READY     0x0E
#घोषणा TIC_ACK_FROM_PC       0x0F
#घोषणा NUMCARD_ACK_FROM_PC   0x010
#घोषणा TYP_ACK_FROM_PC       0x011
#घोषणा CONF_END_TEST         0x012
#घोषणा ERROR_CODE            0x016 
#घोषणा PARAMETER_ERROR       0x018 
#घोषणा VERS                  0x01E 
#घोषणा RAM_TO_PC             0x040
#घोषणा RAM_FROM_PC           0x0170
#घोषणा TYPE_CARD             0x03C0
#घोषणा SERIAL_NUMBER         0x03DA
#घोषणा RAM_IT_FROM_PC        0x03FE
#घोषणा RAM_IT_TO_PC          0x03FF

काष्ठा mailboxअणु
	u16  stjb_codef;		/* offset 00 */
	s16  stjb_status;     		/* offset 02 */
	u16  stjb_ticuser_root;		/* offset 04 */
	u8   stjb_piduser[4];		/* offset 06 */
	u16  stjb_mode;			/* offset 0A */
	u16  stjb_समय;			/* offset 0C */
	u16  stjb_stop;			/* offset 0E */
	u16  stjb_nfonc;		/* offset 10 */
	u16  stjb_ncard;		/* offset 12 */
	u16  stjb_nchan;		/* offset 14 */
	u16  stjb_nes;			/* offset 16 */
	u16  stjb_nb;			/* offset 18 */
	u16  stjb_typvar;		/* offset 1A */
	u32  stjb_adr;			/* offset 1C */
	u16  stjb_ticuser_dispcyc;	/* offset 20 */
	u16  stjb_ticuser_protocol;	/* offset 22 */
	u8   stjb_filler[12];		/* offset 24 */
	u8   stjb_data[256];		/* offset 30 */
	पूर्ण;

काष्ठा st_ram_io 
अणु
	अचिन्हित अक्षर data_to_pc_पढ़ोy;
	अचिन्हित अक्षर tic_owner_to_pc;
	अचिन्हित अक्षर numcard_owner_to_pc;
	अचिन्हित अक्षर tic_des_to_pc;
	अचिन्हित अक्षर numcard_des_to_pc;
	अचिन्हित अक्षर data_from_pc_पढ़ोy;
	अचिन्हित अक्षर tic_owner_from_pc;
	अचिन्हित अक्षर numcard_owner_from_pc;
	अचिन्हित अक्षर tic_des_from_pc;
	अचिन्हित अक्षर numcard_des_from_pc;
	अचिन्हित अक्षर ack_to_pc_पढ़ोy;
	अचिन्हित अक्षर tic_ack_to_pc;
	अचिन्हित अक्षर numcard_ack_to_pc;
	अचिन्हित अक्षर typ_ack_to_pc;
	अचिन्हित अक्षर ack_from_pc_पढ़ोy;
	अचिन्हित अक्षर tic_ack_from_pc;
	अचिन्हित अक्षर numcard_ack_from_pc;
	अचिन्हित अक्षर typ_ack_from_pc;
	अचिन्हित अक्षर conf_end_test[4];
	अचिन्हित अक्षर error_code[2];
	अचिन्हित अक्षर parameter_error[4];
	अचिन्हित अक्षर समय_base;
	अचिन्हित अक्षर nul_inc;
	अचिन्हित अक्षर vers;
	अचिन्हित अक्षर num_card;
	अचिन्हित अक्षर reserv1[32];
पूर्ण;


#पूर्ण_अगर /* __LINUX_APPLICOM_H__ */
