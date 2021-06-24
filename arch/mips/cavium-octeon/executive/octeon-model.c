<शैली गुरु>
/***********************license start***************
 * Author: Cavium Networks
 *
 * Contact: support@caviumnetworks.com
 * This file is part of the OCTEON SDK
 *
 * Copyright (c) 2003-2017 Cavium, Inc.
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this file; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA 02110-1301 USA
 * or visit http://www.gnu.org/licenses/.
 *
 * This file may also be available under a dअगरferent license from Cavium.
 * Contact Cavium Networks क्रम more inक्रमmation
 ***********************license end**************************************/

#समावेश <यंत्र/octeon/octeon.h>

क्रमागत octeon_feature_bits __octeon_feature_bits __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(__octeon_feature_bits);

/**
 * Read a byte of fuse data
 * @byte_addr:	 address to पढ़ो
 *
 * Returns fuse value: 0 or 1
 */
अटल uपूर्णांक8_t __init cvmx_fuse_पढ़ो_byte(पूर्णांक byte_addr)
अणु
	जोड़ cvmx_mio_fus_rcmd पढ़ो_cmd;

	पढ़ो_cmd.u64 = 0;
	पढ़ो_cmd.s.addr = byte_addr;
	पढ़ो_cmd.s.pend = 1;
	cvmx_ग_लिखो_csr(CVMX_MIO_FUS_RCMD, पढ़ो_cmd.u64);
	जबतक ((पढ़ो_cmd.u64 = cvmx_पढ़ो_csr(CVMX_MIO_FUS_RCMD))
	       && पढ़ो_cmd.s.pend)
		;
	वापस पढ़ो_cmd.s.dat;
पूर्ण

/*
 * Version of octeon_model_get_string() that takes buffer as argument,
 * as running early in u-boot अटल/global variables करोn't work when
 * running from flash.
 */
अटल स्थिर अक्षर *__init octeon_model_get_string_buffer(uपूर्णांक32_t chip_id,
							 अक्षर *buffer)
अणु
	स्थिर अक्षर *family;
	स्थिर अक्षर *core_model;
	अक्षर pass[4];
	पूर्णांक घड़ी_mhz;
	स्थिर अक्षर *suffix;
	पूर्णांक num_cores;
	जोड़ cvmx_mio_fus_dat2 fus_dat2;
	जोड़ cvmx_mio_fus_dat3 fus_dat3;
	अक्षर fuse_model[10];
	uपूर्णांक32_t fuse_data = 0;
	uपूर्णांक64_t l2d_fus3 = 0;

	अगर (OCTEON_IS_MODEL(OCTEON_CN3XXX) || OCTEON_IS_MODEL(OCTEON_CN5XXX))
		l2d_fus3 = (cvmx_पढ़ो_csr(CVMX_L2D_FUS3) >> 34) & 0x3;
	fus_dat2.u64 = cvmx_पढ़ो_csr(CVMX_MIO_FUS_DAT2);
	fus_dat3.u64 = cvmx_पढ़ो_csr(CVMX_MIO_FUS_DAT3);
	num_cores = cvmx_octeon_num_cores();

	/* Make sure the non existent devices look disabled */
	चयन ((chip_id >> 8) & 0xff) अणु
	हाल 6:		/* CN50XX */
	हाल 2:		/* CN30XX */
		fus_dat3.s.nodfa_dte = 1;
		fus_dat3.s.nozip = 1;
		अवरोध;
	हाल 4:		/* CN57XX or CN56XX */
		fus_dat3.s.nodfa_dte = 1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Make a guess at the suffix */
	/* NSP = everything */
	/* EXP = No crypto */
	/* SCP = No DFA, No zip */
	/* CP = No DFA, No crypto, No zip */
	अगर (fus_dat3.s.nodfa_dte) अणु
		अगर (fus_dat2.s.nocrypto)
			suffix = "CP";
		अन्यथा
			suffix = "SCP";
	पूर्ण अन्यथा अगर (fus_dat2.s.nocrypto)
		suffix = "EXP";
	अन्यथा
		suffix = "NSP";

	अगर (!fus_dat2.s.nocrypto)
		__octeon_feature_bits |= OCTEON_HAS_CRYPTO;

	/*
	 * Assume pass number is encoded using <5:3><2:0>. Exceptions
	 * will be fixed later.
	 */
	प्र_लिखो(pass, "%d.%d", (पूर्णांक)((chip_id >> 3) & 7) + 1, (पूर्णांक)chip_id & 7);

	/*
	 * Use the number of cores to determine the last 2 digits of
	 * the model number. There are some exceptions that are fixed
	 * later.
	 */
	चयन (num_cores) अणु
	हाल 48:
		core_model = "90";
		अवरोध;
	हाल 44:
		core_model = "88";
		अवरोध;
	हाल 40:
		core_model = "85";
		अवरोध;
	हाल 32:
		core_model = "80";
		अवरोध;
	हाल 24:
		core_model = "70";
		अवरोध;
	हाल 16:
		core_model = "60";
		अवरोध;
	हाल 15:
		core_model = "58";
		अवरोध;
	हाल 14:
		core_model = "55";
		अवरोध;
	हाल 13:
		core_model = "52";
		अवरोध;
	हाल 12:
		core_model = "50";
		अवरोध;
	हाल 11:
		core_model = "48";
		अवरोध;
	हाल 10:
		core_model = "45";
		अवरोध;
	हाल 9:
		core_model = "42";
		अवरोध;
	हाल 8:
		core_model = "40";
		अवरोध;
	हाल 7:
		core_model = "38";
		अवरोध;
	हाल 6:
		core_model = "34";
		अवरोध;
	हाल 5:
		core_model = "32";
		अवरोध;
	हाल 4:
		core_model = "30";
		अवरोध;
	हाल 3:
		core_model = "25";
		अवरोध;
	हाल 2:
		core_model = "20";
		अवरोध;
	हाल 1:
		core_model = "10";
		अवरोध;
	शेष:
		core_model = "XX";
		अवरोध;
	पूर्ण

	/* Now figure out the family, the first two digits */
	चयन ((chip_id >> 8) & 0xff) अणु
	हाल 0:		/* CN38XX, CN37XX or CN36XX */
		अगर (l2d_fus3) अणु
			/*
			 * For some unknown reason, the 16 core one is
			 * called 37 instead of 36.
			 */
			अगर (num_cores >= 16)
				family = "37";
			अन्यथा
				family = "36";
		पूर्ण अन्यथा
			family = "38";
		/*
		 * This series of chips didn't follow the standard
		 * pass numbering.
		 */
		चयन (chip_id & 0xf) अणु
		हाल 0:
			म_नकल(pass, "1.X");
			अवरोध;
		हाल 1:
			म_नकल(pass, "2.X");
			अवरोध;
		हाल 3:
			म_नकल(pass, "3.X");
			अवरोध;
		शेष:
			म_नकल(pass, "X.X");
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 1:		/* CN31XX or CN3020 */
		अगर ((chip_id & 0x10) || l2d_fus3)
			family = "30";
		अन्यथा
			family = "31";
		/*
		 * This series of chips didn't follow the standard
		 * pass numbering.
		 */
		चयन (chip_id & 0xf) अणु
		हाल 0:
			म_नकल(pass, "1.0");
			अवरोध;
		हाल 2:
			म_नकल(pass, "1.1");
			अवरोध;
		शेष:
			म_नकल(pass, "X.X");
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 2:		/* CN3010 or CN3005 */
		family = "30";
		/* A chip with half cache is an 05 */
		अगर (l2d_fus3)
			core_model = "05";
		/*
		 * This series of chips didn't follow the standard
		 * pass numbering.
		 */
		चयन (chip_id & 0xf) अणु
		हाल 0:
			म_नकल(pass, "1.0");
			अवरोध;
		हाल 2:
			म_नकल(pass, "1.1");
			अवरोध;
		शेष:
			म_नकल(pass, "X.X");
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 3:		/* CN58XX */
		family = "58";
		/* Special हाल. 4 core, half cache (CP with half cache) */
		अगर ((num_cores == 4) && l2d_fus3 && !म_भेदन(suffix, "CP", 2))
			core_model = "29";

		/* Pass 1 uses dअगरferent encodings क्रम pass numbers */
		अगर ((chip_id & 0xFF) < 0x8) अणु
			चयन (chip_id & 0x3) अणु
			हाल 0:
				म_नकल(pass, "1.0");
				अवरोध;
			हाल 1:
				म_नकल(pass, "1.1");
				अवरोध;
			हाल 3:
				म_नकल(pass, "1.2");
				अवरोध;
			शेष:
				म_नकल(pass, "1.X");
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल 4:		/* CN57XX, CN56XX, CN55XX, CN54XX */
		अगर (fus_dat2.cn56xx.raid_en) अणु
			अगर (l2d_fus3)
				family = "55";
			अन्यथा
				family = "57";
			अगर (fus_dat2.cn56xx.nocrypto)
				suffix = "SP";
			अन्यथा
				suffix = "SSP";
		पूर्ण अन्यथा अणु
			अगर (fus_dat2.cn56xx.nocrypto)
				suffix = "CP";
			अन्यथा अणु
				suffix = "NSP";
				अगर (fus_dat3.s.nozip)
					suffix = "SCP";

				अगर (fus_dat3.cn38xx.bar2_en)
					suffix = "NSPB2";
			पूर्ण
			अगर (l2d_fus3)
				family = "54";
			अन्यथा
				family = "56";
		पूर्ण
		अवरोध;
	हाल 6:		/* CN50XX */
		family = "50";
		अवरोध;
	हाल 7:		/* CN52XX */
		अगर (l2d_fus3)
			family = "51";
		अन्यथा
			family = "52";
		अवरोध;
	हाल 0x93:		/* CN61XX */
		family = "61";
		अगर (fus_dat2.cn61xx.nocrypto && fus_dat2.cn61xx.करोrm_crypto)
			suffix = "AP";
		अगर (fus_dat2.cn61xx.nocrypto)
			suffix = "CP";
		अन्यथा अगर (fus_dat2.cn61xx.करोrm_crypto)
			suffix = "DAP";
		अन्यथा अगर (fus_dat3.cn61xx.nozip)
			suffix = "SCP";
		अवरोध;
	हाल 0x90:		/* CN63XX */
		family = "63";
		अगर (fus_dat3.s.l2c_crip == 2)
			family = "62";
		अगर (num_cores == 6)	/* Other core counts match generic */
			core_model = "35";
		अगर (fus_dat2.cn63xx.nocrypto)
			suffix = "CP";
		अन्यथा अगर (fus_dat2.cn63xx.करोrm_crypto)
			suffix = "DAP";
		अन्यथा अगर (fus_dat3.cn61xx.nozip)
			suffix = "SCP";
		अन्यथा
			suffix = "AAP";
		अवरोध;
	हाल 0x92:		/* CN66XX */
		family = "66";
		अगर (num_cores == 6)	/* Other core counts match generic */
			core_model = "35";
		अगर (fus_dat2.cn66xx.nocrypto && fus_dat2.cn66xx.करोrm_crypto)
			suffix = "AP";
		अगर (fus_dat2.cn66xx.nocrypto)
			suffix = "CP";
		अन्यथा अगर (fus_dat2.cn66xx.करोrm_crypto)
			suffix = "DAP";
		अन्यथा अगर (fus_dat3.cn61xx.nozip)
			suffix = "SCP";
		अन्यथा
			suffix = "AAP";
		अवरोध;
	हाल 0x91:		/* CN68XX */
		family = "68";
		अगर (fus_dat2.cn68xx.nocrypto && fus_dat3.cn61xx.nozip)
			suffix = "CP";
		अन्यथा अगर (fus_dat2.cn68xx.करोrm_crypto)
			suffix = "DAP";
		अन्यथा अगर (fus_dat3.cn61xx.nozip)
			suffix = "SCP";
		अन्यथा अगर (fus_dat2.cn68xx.nocrypto)
			suffix = "SP";
		अन्यथा
			suffix = "AAP";
		अवरोध;
	हाल 0x94:		/* CNF71XX */
		family = "F71";
		अगर (fus_dat3.cn61xx.nozip)
			suffix = "SCP";
		अन्यथा
			suffix = "AAP";
		अवरोध;
	हाल 0x95:		/* CN78XX */
		अगर (num_cores == 6)	/* Other core counts match generic */
			core_model = "35";
		अगर (OCTEON_IS_MODEL(OCTEON_CN76XX))
			family = "76";
		अन्यथा
			family = "78";
		अगर (fus_dat3.cn78xx.l2c_crip == 2)
			family = "77";
		अगर (fus_dat3.cn78xx.nozip
		    && fus_dat3.cn78xx.nodfa_dte
		    && fus_dat3.cn78xx.nohna_dte) अणु
			अगर (fus_dat3.cn78xx.nozip &&
				!fus_dat2.cn78xx.raid_en &&
				fus_dat3.cn78xx.nohna_dte) अणु
				suffix = "CP";
			पूर्ण अन्यथा अणु
				suffix = "SCP";
			पूर्ण
		पूर्ण अन्यथा अगर (fus_dat2.cn78xx.raid_en == 0)
			suffix = "HCP";
		अन्यथा
			suffix = "AAP";
		अवरोध;
	हाल 0x96:		/* CN70XX */
		family = "70";
		अगर (cvmx_पढ़ो_csr(CVMX_MIO_FUS_PDF) & (0x1ULL << 32))
			family = "71";
		अगर (fus_dat2.cn70xx.nocrypto)
			suffix = "CP";
		अन्यथा अगर (fus_dat3.cn70xx.nodfa_dte)
			suffix = "SCP";
		अन्यथा
			suffix = "AAP";
		अवरोध;
	हाल 0x97:		/* CN73XX */
		अगर (num_cores == 6)	/* Other core counts match generic */
			core_model = "35";
		family = "73";
		अगर (fus_dat3.cn73xx.l2c_crip == 2)
			family = "72";
		अगर (fus_dat3.cn73xx.nozip
				&& fus_dat3.cn73xx.nodfa_dte
				&& fus_dat3.cn73xx.nohna_dte) अणु
			अगर (!fus_dat2.cn73xx.raid_en)
				suffix = "CP";
			अन्यथा
				suffix = "SCP";
		पूर्ण अन्यथा
			suffix = "AAP";
		अवरोध;
	हाल 0x98:		/* CN75XX */
		family = "F75";
		अगर (fus_dat3.cn78xx.nozip
		    && fus_dat3.cn78xx.nodfa_dte
		    && fus_dat3.cn78xx.nohna_dte)
			suffix = "SCP";
		अन्यथा
			suffix = "AAP";
		अवरोध;
	शेष:
		family = "XX";
		core_model = "XX";
		म_नकल(pass, "X.X");
		suffix = "XXX";
		अवरोध;
	पूर्ण

	घड़ी_mhz = octeon_get_घड़ी_rate() / 1000000;
	अगर (family[0] != '3') अणु
		पूर्णांक fuse_base = 384 / 8;
		अगर (family[0] == '6')
			fuse_base = 832 / 8;

		/* Check क्रम model in fuses, overrides normal decode */
		/* This is _not_ valid क्रम Octeon CN3XXX models */
		fuse_data |= cvmx_fuse_पढ़ो_byte(fuse_base + 3);
		fuse_data = fuse_data << 8;
		fuse_data |= cvmx_fuse_पढ़ो_byte(fuse_base + 2);
		fuse_data = fuse_data << 8;
		fuse_data |= cvmx_fuse_पढ़ो_byte(fuse_base + 1);
		fuse_data = fuse_data << 8;
		fuse_data |= cvmx_fuse_पढ़ो_byte(fuse_base);
		अगर (fuse_data & 0x7ffff) अणु
			पूर्णांक model = fuse_data & 0x3fff;
			पूर्णांक suffix = (fuse_data >> 14) & 0x1f;
			अगर (suffix && model) अणु
				/* Have both number and suffix in fuses, so both */
				प्र_लिखो(fuse_model, "%d%c", model, 'A' + suffix - 1);
				core_model = "";
				family = fuse_model;
			पूर्ण अन्यथा अगर (suffix && !model) अणु
				/* Only have suffix, so add suffix to 'normal' model number */
				प्र_लिखो(fuse_model, "%s%c", core_model, 'A' + suffix - 1);
				core_model = fuse_model;
			पूर्ण अन्यथा अणु
				/* Don't have suffix, so just use model from fuses */
				प्र_लिखो(fuse_model, "%d", model);
				core_model = "";
				family = fuse_model;
			पूर्ण
		पूर्ण
	पूर्ण
	प्र_लिखो(buffer, "CN%s%sp%s-%d-%s", family, core_model, pass, घड़ी_mhz, suffix);
	वापस buffer;
पूर्ण

/**
 * Given the chip processor ID from COP0, this function वापसs a
 * string representing the chip model number. The string is of the
 * क्रमm CNXXXXpX.X-FREQ-SUFFIX.
 * - XXXX = The chip model number
 * - X.X = Chip pass number
 * - FREQ = Current frequency in Mhz
 * - SUFFIX = NSP, EXP, SCP, SSP, or CP
 *
 * @chip_id: Chip ID
 *
 * Returns Model string
 */
स्थिर अक्षर *__init octeon_model_get_string(uपूर्णांक32_t chip_id)
अणु
	अटल अक्षर buffer[32];
	वापस octeon_model_get_string_buffer(chip_id, buffer);
पूर्ण
