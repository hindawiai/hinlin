<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vivid-rds-gen.c - rds (radio data प्रणाली) generator support functions.
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/माला.स>
#समावेश <linux/videodev2.h>

#समावेश "vivid-rds-gen.h"

अटल u8 vivid_get_di(स्थिर काष्ठा vivid_rds_gen *rds, अचिन्हित grp)
अणु
	चयन (grp) अणु
	हाल 0:
		वापस (rds->dyn_pty << 2) | (grp & 3);
	हाल 1:
		वापस (rds->compressed << 2) | (grp & 3);
	हाल 2:
		वापस (rds->art_head << 2) | (grp & 3);
	हाल 3:
		वापस (rds->mono_stereo << 2) | (grp & 3);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This RDS generator creates 57 RDS groups (one group == four RDS blocks).
 * Groups 0-3, 22-25 and 44-47 (spaced 22 groups apart) are filled with a
 * standard 0B group containing the PI code and PS name.
 *
 * Groups 4-19 and 26-41 use group 2A क्रम the radio text.
 *
 * Group 56 contains the समय (group 4A).
 *
 * All reमुख्यing groups use a filler group 15B block that just repeats
 * the PI and PTY codes.
 */
व्योम vivid_rds_generate(काष्ठा vivid_rds_gen *rds)
अणु
	काष्ठा v4l2_rds_data *data = rds->data;
	अचिन्हित grp;
	अचिन्हित idx;
	काष्ठा पंचांग पंचांग;
	अचिन्हित date;
	अचिन्हित समय;
	पूर्णांक l;

	क्रम (grp = 0; grp < VIVID_RDS_GEN_GROUPS; grp++, data += VIVID_RDS_GEN_BLKS_PER_GRP) अणु
		data[0].lsb = rds->picode & 0xff;
		data[0].msb = rds->picode >> 8;
		data[0].block = V4L2_RDS_BLOCK_A | (V4L2_RDS_BLOCK_A << 3);
		data[1].lsb = rds->pty << 5;
		data[1].msb = (rds->pty >> 3) | (rds->tp << 2);
		data[1].block = V4L2_RDS_BLOCK_B | (V4L2_RDS_BLOCK_B << 3);
		data[3].block = V4L2_RDS_BLOCK_D | (V4L2_RDS_BLOCK_D << 3);

		चयन (grp) अणु
		हाल 0 ... 3:
		हाल 22 ... 25:
		हाल 44 ... 47: /* Group 0B */
			idx = (grp % 22) % 4;
			data[1].lsb |= (rds->ta << 4) | (rds->ms << 3);
			data[1].lsb |= vivid_get_di(rds, idx);
			data[1].msb |= 1 << 3;
			data[2].lsb = rds->picode & 0xff;
			data[2].msb = rds->picode >> 8;
			data[2].block = V4L2_RDS_BLOCK_C_ALT | (V4L2_RDS_BLOCK_C_ALT << 3);
			data[3].lsb = rds->psname[2 * idx + 1];
			data[3].msb = rds->psname[2 * idx];
			अवरोध;
		हाल 4 ... 19:
		हाल 26 ... 41: /* Group 2A */
			idx = ((grp - 4) % 22) % 16;
			data[1].lsb |= idx;
			data[1].msb |= 4 << 3;
			data[2].msb = rds->radiotext[4 * idx];
			data[2].lsb = rds->radiotext[4 * idx + 1];
			data[2].block = V4L2_RDS_BLOCK_C | (V4L2_RDS_BLOCK_C << 3);
			data[3].msb = rds->radiotext[4 * idx + 2];
			data[3].lsb = rds->radiotext[4 * idx + 3];
			अवरोध;
		हाल 56:
			/*
			 * Group 4A
			 *
			 * Uses the algorithm from Annex G of the RDS standard
			 * EN 50067:1998 to convert a UTC date to an RDS Modअगरied
			 * Julian Day.
			 */
			समय64_to_पंचांग(kसमय_get_real_seconds(), 0, &पंचांग);
			l = पंचांग.पंचांग_mon <= 1;
			date = 14956 + पंचांग.पंचांग_mday + ((पंचांग.पंचांग_year - l) * 1461) / 4 +
				((पंचांग.पंचांग_mon + 2 + l * 12) * 306001) / 10000;
			समय = (पंचांग.पंचांग_hour << 12) |
			       (पंचांग.पंचांग_min << 6) |
			       (sys_tz.tz_minuteswest >= 0 ? 0x20 : 0) |
			       (असल(sys_tz.tz_minuteswest) / 30);
			data[1].lsb &= ~3;
			data[1].lsb |= date >> 15;
			data[1].msb |= 8 << 3;
			data[2].lsb = (date << 1) & 0xfe;
			data[2].lsb |= (समय >> 16) & 1;
			data[2].msb = (date >> 7) & 0xff;
			data[2].block = V4L2_RDS_BLOCK_C | (V4L2_RDS_BLOCK_C << 3);
			data[3].lsb = समय & 0xff;
			data[3].msb = (समय >> 8) & 0xff;
			अवरोध;
		शेष: /* Group 15B */
			data[1].lsb |= (rds->ta << 4) | (rds->ms << 3);
			data[1].lsb |= vivid_get_di(rds, grp % 22);
			data[1].msb |= 0x1f << 3;
			data[2].lsb = rds->picode & 0xff;
			data[2].msb = rds->picode >> 8;
			data[2].block = V4L2_RDS_BLOCK_C_ALT | (V4L2_RDS_BLOCK_C_ALT << 3);
			data[3].lsb = rds->pty << 5;
			data[3].lsb |= (rds->ta << 4) | (rds->ms << 3);
			data[3].lsb |= vivid_get_di(rds, grp % 22);
			data[3].msb |= rds->pty >> 3;
			data[3].msb |= 0x1f << 3;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम vivid_rds_gen_fill(काष्ठा vivid_rds_gen *rds, अचिन्हित freq,
			  bool alt)
अणु
	/* Alternate PTY between Info and Weather */
	अगर (rds->use_rbds) अणु
		rds->picode = 0x2e75; /* 'KLNX' call sign */
		rds->pty = alt ? 29 : 2;
	पूर्ण अन्यथा अणु
		rds->picode = 0x8088;
		rds->pty = alt ? 16 : 3;
	पूर्ण
	rds->mono_stereo = true;
	rds->art_head = false;
	rds->compressed = false;
	rds->dyn_pty = false;
	rds->tp = true;
	rds->ta = alt;
	rds->ms = true;
	snम_लिखो(rds->psname, माप(rds->psname), "%6d.%1d",
		 freq / 16, ((freq & 0xf) * 10) / 16);
	अगर (alt)
		strscpy(rds->radiotext,
			" The Radio Data System can switch between different Radio Texts ",
			माप(rds->radiotext));
	अन्यथा
		strscpy(rds->radiotext,
			"An example of Radio Text as transmitted by the Radio Data System",
			माप(rds->radiotext));
पूर्ण
