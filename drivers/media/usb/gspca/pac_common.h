<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Pixart PAC207BCA / PAC73xx common functions
 *
 * Copyright (C) 2008 Hans de Goede <j.w.r.degoede@hhs.nl>
 * Copyright (C) 2005 Thomas Kaiser thomas@kaiser-linux.li
 * Copyleft (C) 2005 Michel Xhaard mxhaard@magic.fr
 *
 * V4L2 by Jean-Francois Moine <http://moinejf.मुक्त.fr>
 */

/* We calculate the स्वतःgain at the end of the transfer of a frame, at this
   moment a frame with the old settings is being captured and transmitted. So
   अगर we adjust the gain or exposure we must ignore at least the next frame क्रम
   the new settings to come पूर्णांकo effect beक्रमe करोing any other adjusपंचांगents. */
#घोषणा PAC_AUTOGAIN_IGNORE_FRAMES	2

अटल स्थिर अचिन्हित अक्षर pac_sof_marker[5] =
		अणु 0xff, 0xff, 0x00, 0xff, 0x96 पूर्ण;

/*
   The following state machine finds the SOF marker sequence
   0xff, 0xff, 0x00, 0xff, 0x96 in a byte stream.

	   +----------+
	   | 0: START |<---------------\
	   +----------+<-\             |
	     |       \---/otherwise    |
	     v 0xff                    |
	   +----------+ otherwise      |
	   |     1    |--------------->*
	   |          |                ^
	   +----------+                |
	     |                         |
	     v 0xff                    |
	   +----------+<-\0xff         |
	/->|          |--/             |
	|  |     2    |--------------->*
	|  |          | otherwise      ^
	|  +----------+                |
	|    |                         |
	|    v 0x00                    |
	|  +----------+                |
	|  |     3    |                |
	|  |          |--------------->*
	|  +----------+ otherwise      ^
	|    |                         |
   0xff |    v 0xff                    |
	|  +----------+                |
	\--|     4    |                |
	   |          |----------------/
	   +----------+ otherwise
	     |
	     v 0x96
	   +----------+
	   |  FOUND   |
	   +----------+
*/

अटल अचिन्हित अक्षर *pac_find_sof(काष्ठा gspca_dev *gspca_dev, u8 *sof_पढ़ो,
					अचिन्हित अक्षर *m, पूर्णांक len)
अणु
	पूर्णांक i;

	/* Search क्रम the SOF marker (fixed part) in the header */
	क्रम (i = 0; i < len; i++) अणु
		चयन (*sof_पढ़ो) अणु
		हाल 0:
			अगर (m[i] == 0xff)
				*sof_पढ़ो = 1;
			अवरोध;
		हाल 1:
			अगर (m[i] == 0xff)
				*sof_पढ़ो = 2;
			अन्यथा
				*sof_पढ़ो = 0;
			अवरोध;
		हाल 2:
			चयन (m[i]) अणु
			हाल 0x00:
				*sof_पढ़ो = 3;
				अवरोध;
			हाल 0xff:
				/* stay in this state */
				अवरोध;
			शेष:
				*sof_पढ़ो = 0;
			पूर्ण
			अवरोध;
		हाल 3:
			अगर (m[i] == 0xff)
				*sof_पढ़ो = 4;
			अन्यथा
				*sof_पढ़ो = 0;
			अवरोध;
		हाल 4:
			चयन (m[i]) अणु
			हाल 0x96:
				/* Pattern found */
				gspca_dbg(gspca_dev, D_FRAM,
					  "SOF found, bytes to analyze: %u - Frame starts at byte #%u\n",
					  len, i + 1);
				*sof_पढ़ो = 0;
				वापस m + i + 1;
				अवरोध;
			हाल 0xff:
				*sof_पढ़ो = 2;
				अवरोध;
			शेष:
				*sof_पढ़ो = 0;
			पूर्ण
			अवरोध;
		शेष:
			*sof_पढ़ो = 0;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण
