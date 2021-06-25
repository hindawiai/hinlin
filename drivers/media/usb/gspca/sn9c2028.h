<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * SN9C2028 common functions
 *
 * Copyright (C) 2009 Theoकरोre Kilgore <kilgota@auburn,edu>
 *
 * Based बंदly upon the file gspca/pac_common.h
 */

अटल स्थिर अचिन्हित अक्षर sn9c2028_sof_marker[] = अणु
	0xff, 0xff, 0x00, 0xc4, 0xc4, 0x96,
	0x00,
	0x00, /* seq */
	0x00,
	0x00,
	0x00, /* avg luminance lower 8 bit */
	0x00, /* avg luminance higher 8 bit */
पूर्ण;

अटल अचिन्हित अक्षर *sn9c2028_find_sof(काष्ठा gspca_dev *gspca_dev,
					अचिन्हित अक्षर *m, पूर्णांक len)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक i;

	/* Search क्रम the SOF marker (fixed part) in the header */
	क्रम (i = 0; i < len; i++) अणु
		अगर ((m[i] == sn9c2028_sof_marker[sd->sof_पढ़ो]) ||
		    (sd->sof_पढ़ो > 5)) अणु
			sd->sof_पढ़ो++;
			अगर (sd->sof_पढ़ो == 11)
				sd->avg_lum_l = m[i];
			अगर (sd->sof_पढ़ो == 12)
				sd->avg_lum = (m[i] << 8) + sd->avg_lum_l;
			अगर (sd->sof_पढ़ो == माप(sn9c2028_sof_marker)) अणु
				gspca_dbg(gspca_dev, D_FRAM,
					  "SOF found, bytes to analyze: %u - Frame starts at byte #%u\n",
					  len, i + 1);
				sd->sof_पढ़ो = 0;
				वापस m + i + 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			sd->sof_पढ़ो = 0;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण
