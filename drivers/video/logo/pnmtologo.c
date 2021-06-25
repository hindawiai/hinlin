<शैली गुरु>

/*
 *  Convert a logo in ASCII PNM क्रमmat to C source suitable क्रम inclusion in
 *  the Linux kernel
 *
 *  (C) Copyright 2001-2003 by Geert Uytterhoeven <geert@linux-m68k.org>
 *
 *  --------------------------------------------------------------------------
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of the Linux
 *  distribution क्रम more details.
 */

#समावेश <प्रकार.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानकतर्क.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>


अटल स्थिर अक्षर *programname;
अटल स्थिर अक्षर *filename;
अटल स्थिर अक्षर *logoname = "linux_logo";
अटल स्थिर अक्षर *outputname;
अटल खाता *out;


#घोषणा LINUX_LOGO_MONO		1	/* monochrome black/white */
#घोषणा LINUX_LOGO_VGA16	2	/* 16 colors VGA text palette */
#घोषणा LINUX_LOGO_CLUT224	3	/* 224 colors */
#घोषणा LINUX_LOGO_GRAY256	4	/* 256 levels grayscale */

अटल स्थिर अक्षर *logo_types[LINUX_LOGO_GRAY256+1] = अणु
    [LINUX_LOGO_MONO] = "LINUX_LOGO_MONO",
    [LINUX_LOGO_VGA16] = "LINUX_LOGO_VGA16",
    [LINUX_LOGO_CLUT224] = "LINUX_LOGO_CLUT224",
    [LINUX_LOGO_GRAY256] = "LINUX_LOGO_GRAY256"
पूर्ण;

#घोषणा MAX_LINUX_LOGO_COLORS	224

काष्ठा color अणु
    अचिन्हित अक्षर red;
    अचिन्हित अक्षर green;
    अचिन्हित अक्षर blue;
पूर्ण;

अटल स्थिर काष्ठा color clut_vga16[16] = अणु
    अणु 0x00, 0x00, 0x00 पूर्ण,
    अणु 0x00, 0x00, 0xaa पूर्ण,
    अणु 0x00, 0xaa, 0x00 पूर्ण,
    अणु 0x00, 0xaa, 0xaa पूर्ण,
    अणु 0xaa, 0x00, 0x00 पूर्ण,
    अणु 0xaa, 0x00, 0xaa पूर्ण,
    अणु 0xaa, 0x55, 0x00 पूर्ण,
    अणु 0xaa, 0xaa, 0xaa पूर्ण,
    अणु 0x55, 0x55, 0x55 पूर्ण,
    अणु 0x55, 0x55, 0xff पूर्ण,
    अणु 0x55, 0xff, 0x55 पूर्ण,
    अणु 0x55, 0xff, 0xff पूर्ण,
    अणु 0xff, 0x55, 0x55 पूर्ण,
    अणु 0xff, 0x55, 0xff पूर्ण,
    अणु 0xff, 0xff, 0x55 पूर्ण,
    अणु 0xff, 0xff, 0xff पूर्ण,
पूर्ण;


अटल पूर्णांक logo_type = LINUX_LOGO_CLUT224;
अटल अचिन्हित पूर्णांक logo_width;
अटल अचिन्हित पूर्णांक logo_height;
अटल काष्ठा color **logo_data;
अटल काष्ठा color logo_clut[MAX_LINUX_LOGO_COLORS];
अटल अचिन्हित पूर्णांक logo_clutsize;
अटल पूर्णांक is_plain_pbm = 0;

अटल व्योम die(स्थिर अक्षर *fmt, ...)
    __attribute__ ((noवापस)) __attribute ((क्रमmat (म_लिखो, 1, 2)));
अटल व्योम usage(व्योम) __attribute ((noवापस));


अटल अचिन्हित पूर्णांक get_number(खाता *fp)
अणु
    पूर्णांक c, val;

    /* Skip leading whitespace */
    करो अणु
	c = ख_अक्षर_लो(fp);
	अगर (c == खातापूर्ण)
	    die("%s: end of file\n", filename);
	अगर (c == '#') अणु
	    /* Ignore comments 'till end of line */
	    करो अणु
		c = ख_अक्षर_लो(fp);
		अगर (c == खातापूर्ण)
		    die("%s: end of file\n", filename);
	    पूर्ण जबतक (c != '\n');
	पूर्ण
    पूर्ण जबतक (है_खाली(c));

    /* Parse decimal number */
    val = 0;
    जबतक (है_अंक(c)) अणु
	val = 10*val+c-'0';
	/* some PBM are 'broken'; GiMP क्रम example exports a PBM without space
	 * between the digits. This is Ok cause we know a PBM can only have a '1'
	 * or a '0' क्रम the digit. */
	अगर (is_plain_pbm)
		अवरोध;
	c = ख_अक्षर_लो(fp);
	अगर (c == खातापूर्ण)
	    die("%s: end of file\n", filename);
    पूर्ण
    वापस val;
पूर्ण

अटल अचिन्हित पूर्णांक get_number255(खाता *fp, अचिन्हित पूर्णांक maxval)
अणु
    अचिन्हित पूर्णांक val = get_number(fp);
    वापस (255*val+maxval/2)/maxval;
पूर्ण

अटल व्योम पढ़ो_image(व्योम)
अणु
    खाता *fp;
    अचिन्हित पूर्णांक i, j;
    पूर्णांक magic;
    अचिन्हित पूर्णांक maxval;

    /* खोलो image file */
    fp = ख_खोलो(filename, "r");
    अगर (!fp)
	die("Cannot open file %s: %s\n", filename, म_त्रुटि(त्रुटि_सं));

    /* check file type and पढ़ो file header */
    magic = ख_अक्षर_लो(fp);
    अगर (magic != 'P')
	die("%s is not a PNM file\n", filename);
    magic = ख_अक्षर_लो(fp);
    चयन (magic) अणु
	हाल '1':
	हाल '2':
	हाल '3':
	    /* Plain PBM/PGM/PPM */
	    अवरोध;

	हाल '4':
	हाल '5':
	हाल '6':
	    /* Binary PBM/PGM/PPM */
	    die("%s: Binary PNM is not supported\n"
		"Use pnmnoraw(1) to convert it to ASCII PNM\n", filename);

	शेष:
	    die("%s is not a PNM file\n", filename);
    पूर्ण
    logo_width = get_number(fp);
    logo_height = get_number(fp);

    /* allocate image data */
    logo_data = (काष्ठा color **)दो_स्मृति(logo_height*माप(काष्ठा color *));
    अगर (!logo_data)
	die("%s\n", म_त्रुटि(त्रुटि_सं));
    क्रम (i = 0; i < logo_height; i++) अणु
	logo_data[i] = दो_स्मृति(logo_width*माप(काष्ठा color));
	अगर (!logo_data[i])
	    die("%s\n", म_त्रुटि(त्रुटि_सं));
    पूर्ण

    /* पढ़ो image data */
    चयन (magic) अणु
	हाल '1':
	    /* Plain PBM */
	    is_plain_pbm = 1;
	    क्रम (i = 0; i < logo_height; i++)
		क्रम (j = 0; j < logo_width; j++)
		    logo_data[i][j].red = logo_data[i][j].green =
			logo_data[i][j].blue = 255*(1-get_number(fp));
	    अवरोध;

	हाल '2':
	    /* Plain PGM */
	    maxval = get_number(fp);
	    क्रम (i = 0; i < logo_height; i++)
		क्रम (j = 0; j < logo_width; j++)
		    logo_data[i][j].red = logo_data[i][j].green =
			logo_data[i][j].blue = get_number255(fp, maxval);
	    अवरोध;

	हाल '3':
	    /* Plain PPM */
	    maxval = get_number(fp);
	    क्रम (i = 0; i < logo_height; i++)
		क्रम (j = 0; j < logo_width; j++) अणु
		    logo_data[i][j].red = get_number255(fp, maxval);
		    logo_data[i][j].green = get_number255(fp, maxval);
		    logo_data[i][j].blue = get_number255(fp, maxval);
		पूर्ण
	    अवरोध;
    पूर्ण

    /* बंद file */
    ख_बंद(fp);
पूर्ण

अटल अंतरभूत पूर्णांक is_black(काष्ठा color c)
अणु
    वापस c.red == 0 && c.green == 0 && c.blue == 0;
पूर्ण

अटल अंतरभूत पूर्णांक is_white(काष्ठा color c)
अणु
    वापस c.red == 255 && c.green == 255 && c.blue == 255;
पूर्ण

अटल अंतरभूत पूर्णांक is_gray(काष्ठा color c)
अणु
    वापस c.red == c.green && c.red == c.blue;
पूर्ण

अटल अंतरभूत पूर्णांक is_equal(काष्ठा color c1, काष्ठा color c2)
अणु
    वापस c1.red == c2.red && c1.green == c2.green && c1.blue == c2.blue;
पूर्ण

अटल व्योम ग_लिखो_header(व्योम)
अणु
    /* खोलो logo file */
    अगर (outputname) अणु
	out = ख_खोलो(outputname, "w");
	अगर (!out)
	    die("Cannot create file %s: %s\n", outputname, म_त्रुटि(त्रुटि_सं));
    पूर्ण अन्यथा अणु
	out = मानक_निकास;
    पूर्ण

    ख_माला_दो("/*\n", out);
    ख_माला_दो(" *  DO NOT EDIT THIS FILE!\n", out);
    ख_माला_दो(" *\n", out);
    ख_लिखो(out, " *  It was automatically generated from %s\n", filename);
    ख_माला_दो(" *\n", out);
    ख_लिखो(out, " *  Linux logo %s\n", logoname);
    ख_माला_दो(" */\n\n", out);
    ख_माला_दो("#include <linux/linux_logo.h>\n\n", out);
    ख_लिखो(out, "static unsigned char %s_data[] __initdata = {\n",
	    logoname);
पूर्ण

अटल व्योम ग_लिखो_footer(व्योम)
अणु
    ख_माला_दो("\n};\n\n", out);
    ख_लिखो(out, "const struct linux_logo %s __initconst = {\n", logoname);
    ख_लिखो(out, "\t.type\t\t= %s,\n", logo_types[logo_type]);
    ख_लिखो(out, "\t.width\t\t= %d,\n", logo_width);
    ख_लिखो(out, "\t.height\t\t= %d,\n", logo_height);
    अगर (logo_type == LINUX_LOGO_CLUT224) अणु
	ख_लिखो(out, "\t.clutsize\t= %d,\n", logo_clutsize);
	ख_लिखो(out, "\t.clut\t\t= %s_clut,\n", logoname);
    पूर्ण
    ख_लिखो(out, "\t.data\t\t= %s_data\n", logoname);
    ख_माला_दो("};\n\n", out);

    /* बंद logo file */
    अगर (outputname)
	ख_बंद(out);
पूर्ण

अटल पूर्णांक ग_लिखो_hex_cnt;

अटल व्योम ग_लिखो_hex(अचिन्हित अक्षर byte)
अणु
    अगर (ग_लिखो_hex_cnt % 12)
	ख_लिखो(out, ", 0x%02x", byte);
    अन्यथा अगर (ग_लिखो_hex_cnt)
	ख_लिखो(out, ",\n\t0x%02x", byte);
    अन्यथा
	ख_लिखो(out, "\t0x%02x", byte);
    ग_लिखो_hex_cnt++;
पूर्ण

अटल व्योम ग_लिखो_logo_mono(व्योम)
अणु
    अचिन्हित पूर्णांक i, j;
    अचिन्हित अक्षर val, bit;

    /* validate image */
    क्रम (i = 0; i < logo_height; i++)
	क्रम (j = 0; j < logo_width; j++)
	    अगर (!is_black(logo_data[i][j]) && !is_white(logo_data[i][j]))
		die("Image must be monochrome\n");

    /* ग_लिखो file header */
    ग_लिखो_header();

    /* ग_लिखो logo data */
    क्रम (i = 0; i < logo_height; i++) अणु
	क्रम (j = 0; j < logo_width;) अणु
	    क्रम (val = 0, bit = 0x80; bit && j < logo_width; j++, bit >>= 1)
		अगर (logo_data[i][j].red)
		    val |= bit;
	    ग_लिखो_hex(val);
	पूर्ण
    पूर्ण

    /* ग_लिखो logo काष्ठाure and file footer */
    ग_लिखो_footer();
पूर्ण

अटल व्योम ग_लिखो_logo_vga16(व्योम)
अणु
    अचिन्हित पूर्णांक i, j, k;
    अचिन्हित अक्षर val;

    /* validate image */
    क्रम (i = 0; i < logo_height; i++)
	क्रम (j = 0; j < logo_width; j++) अणु
	    क्रम (k = 0; k < 16; k++)
		अगर (is_equal(logo_data[i][j], clut_vga16[k]))
		    अवरोध;
	    अगर (k == 16)
		die("Image must use the 16 console colors only\n"
		    "Use ppmquant(1) -map clut_vga16.ppm to reduce the number "
		    "of colors\n");
	पूर्ण

    /* ग_लिखो file header */
    ग_लिखो_header();

    /* ग_लिखो logo data */
    क्रम (i = 0; i < logo_height; i++)
	क्रम (j = 0; j < logo_width; j++) अणु
	    क्रम (k = 0; k < 16; k++)
		अगर (is_equal(logo_data[i][j], clut_vga16[k]))
		    अवरोध;
	    val = k<<4;
	    अगर (++j < logo_width) अणु
		क्रम (k = 0; k < 16; k++)
		    अगर (is_equal(logo_data[i][j], clut_vga16[k]))
			अवरोध;
		val |= k;
	    पूर्ण
	    ग_लिखो_hex(val);
	पूर्ण

    /* ग_लिखो logo काष्ठाure and file footer */
    ग_लिखो_footer();
पूर्ण

अटल व्योम ग_लिखो_logo_clut224(व्योम)
अणु
    अचिन्हित पूर्णांक i, j, k;

    /* validate image */
    क्रम (i = 0; i < logo_height; i++)
	क्रम (j = 0; j < logo_width; j++) अणु
	    क्रम (k = 0; k < logo_clutsize; k++)
		अगर (is_equal(logo_data[i][j], logo_clut[k]))
		    अवरोध;
	    अगर (k == logo_clutsize) अणु
		अगर (logo_clutsize == MAX_LINUX_LOGO_COLORS)
		    die("Image has more than %d colors\n"
			"Use ppmquant(1) to reduce the number of colors\n",
			MAX_LINUX_LOGO_COLORS);
		logo_clut[logo_clutsize++] = logo_data[i][j];
	    पूर्ण
	पूर्ण

    /* ग_लिखो file header */
    ग_लिखो_header();

    /* ग_लिखो logo data */
    क्रम (i = 0; i < logo_height; i++)
	क्रम (j = 0; j < logo_width; j++) अणु
	    क्रम (k = 0; k < logo_clutsize; k++)
		अगर (is_equal(logo_data[i][j], logo_clut[k]))
		    अवरोध;
	    ग_लिखो_hex(k+32);
	पूर्ण
    ख_माला_दो("\n};\n\n", out);

    /* ग_लिखो logo clut */
    ख_लिखो(out, "static unsigned char %s_clut[] __initdata = {\n",
	    logoname);
    ग_लिखो_hex_cnt = 0;
    क्रम (i = 0; i < logo_clutsize; i++) अणु
	ग_लिखो_hex(logo_clut[i].red);
	ग_लिखो_hex(logo_clut[i].green);
	ग_लिखो_hex(logo_clut[i].blue);
    पूर्ण

    /* ग_लिखो logo काष्ठाure and file footer */
    ग_लिखो_footer();
पूर्ण

अटल व्योम ग_लिखो_logo_gray256(व्योम)
अणु
    अचिन्हित पूर्णांक i, j;

    /* validate image */
    क्रम (i = 0; i < logo_height; i++)
	क्रम (j = 0; j < logo_width; j++)
	    अगर (!is_gray(logo_data[i][j]))
		die("Image must be grayscale\n");

    /* ग_लिखो file header */
    ग_लिखो_header();

    /* ग_लिखो logo data */
    क्रम (i = 0; i < logo_height; i++)
	क्रम (j = 0; j < logo_width; j++)
	    ग_लिखो_hex(logo_data[i][j].red);

    /* ग_लिखो logo काष्ठाure and file footer */
    ग_लिखो_footer();
पूर्ण

अटल व्योम die(स्थिर अक्षर *fmt, ...)
अणु
    बहु_सूची ap;

    बहु_शुरू(ap, fmt);
    भख_लिखो(मानक_त्रुटि, fmt, ap);
    बहु_पूर्ण(ap);

    निकास(1);
पूर्ण

अटल व्योम usage(व्योम)
अणु
    die("\n"
	"Usage: %s [options] <filename>\n"
	"\n"
	"Valid options:\n"
	"    -h          : display this usage information\n"
	"    -n <name>   : specify logo name (default: linux_logo)\n"
	"    -o <output> : output to file <output> instead of stdout\n"
	"    -t <type>   : specify logo type, one of\n"
	"                      mono    : monochrome black/white\n"
	"                      vga16   : 16 colors VGA text palette\n"
	"                      clut224 : 224 colors (default)\n"
	"                      gray256 : 256 levels grayscale\n"
	"\n", programname);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
    पूर्णांक opt;

    programname = argv[0];

    opterr = 0;
    जबतक (1) अणु
	opt = getopt(argc, argv, "hn:o:t:");
	अगर (opt == -1)
	    अवरोध;

	चयन (opt) अणु
	    हाल 'h':
		usage();
		अवरोध;

	    हाल 'n':
		logoname = optarg;
		अवरोध;

	    हाल 'o':
		outputname = optarg;
		अवरोध;

	    हाल 't':
		अगर (!म_भेद(optarg, "mono"))
		    logo_type = LINUX_LOGO_MONO;
		अन्यथा अगर (!म_भेद(optarg, "vga16"))
		    logo_type = LINUX_LOGO_VGA16;
		अन्यथा अगर (!म_भेद(optarg, "clut224"))
		    logo_type = LINUX_LOGO_CLUT224;
		अन्यथा अगर (!म_भेद(optarg, "gray256"))
		    logo_type = LINUX_LOGO_GRAY256;
		अन्यथा
		    usage();
		अवरोध;

	    शेष:
		usage();
		अवरोध;
	पूर्ण
    पूर्ण
    अगर (optind != argc-1)
	usage();

    filename = argv[optind];

    पढ़ो_image();
    चयन (logo_type) अणु
	हाल LINUX_LOGO_MONO:
	    ग_लिखो_logo_mono();
	    अवरोध;

	हाल LINUX_LOGO_VGA16:
	    ग_लिखो_logo_vga16();
	    अवरोध;

	हाल LINUX_LOGO_CLUT224:
	    ग_लिखो_logo_clut224();
	    अवरोध;

	हाल LINUX_LOGO_GRAY256:
	    ग_लिखो_logo_gray256();
	    अवरोध;
    पूर्ण
    निकास(0);
पूर्ण
