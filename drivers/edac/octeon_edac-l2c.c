<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2012 Cavium, Inc.
 *
 * Copyright (C) 2009 Wind River Systems,
 *   written by Ralf Baechle <ralf@linux-mips.org>
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/edac.h>

#समावेश <यंत्र/octeon/cvmx.h>

#समावेश "edac_module.h"

#घोषणा EDAC_MOD_STR "octeon-l2c"

अटल व्योम octeon_l2c_poll_oct1(काष्ठा edac_device_ctl_info *l2c)
अणु
	जोड़ cvmx_l2t_err l2t_err, l2t_err_reset;
	जोड़ cvmx_l2d_err l2d_err, l2d_err_reset;

	l2t_err_reset.u64 = 0;
	l2t_err.u64 = cvmx_पढ़ो_csr(CVMX_L2T_ERR);
	अगर (l2t_err.s.sec_err) अणु
		edac_device_handle_ce(l2c, 0, 0,
				      "Tag Single bit error (corrected)");
		l2t_err_reset.s.sec_err = 1;
	पूर्ण
	अगर (l2t_err.s.ded_err) अणु
		edac_device_handle_ue(l2c, 0, 0,
				      "Tag Double bit error (detected)");
		l2t_err_reset.s.ded_err = 1;
	पूर्ण
	अगर (l2t_err_reset.u64)
		cvmx_ग_लिखो_csr(CVMX_L2T_ERR, l2t_err_reset.u64);

	l2d_err_reset.u64 = 0;
	l2d_err.u64 = cvmx_पढ़ो_csr(CVMX_L2D_ERR);
	अगर (l2d_err.s.sec_err) अणु
		edac_device_handle_ce(l2c, 0, 1,
				      "Data Single bit error (corrected)");
		l2d_err_reset.s.sec_err = 1;
	पूर्ण
	अगर (l2d_err.s.ded_err) अणु
		edac_device_handle_ue(l2c, 0, 1,
				      "Data Double bit error (detected)");
		l2d_err_reset.s.ded_err = 1;
	पूर्ण
	अगर (l2d_err_reset.u64)
		cvmx_ग_लिखो_csr(CVMX_L2D_ERR, l2d_err_reset.u64);

पूर्ण

अटल व्योम _octeon_l2c_poll_oct2(काष्ठा edac_device_ctl_info *l2c, पूर्णांक tad)
अणु
	जोड़ cvmx_l2c_err_tdtx err_tdtx, err_tdtx_reset;
	जोड़ cvmx_l2c_err_ttgx err_ttgx, err_ttgx_reset;
	अक्षर buf1[64];
	अक्षर buf2[80];

	err_tdtx_reset.u64 = 0;
	err_tdtx.u64 = cvmx_पढ़ो_csr(CVMX_L2C_ERR_TDTX(tad));
	अगर (err_tdtx.s.dbe || err_tdtx.s.sbe ||
	    err_tdtx.s.vdbe || err_tdtx.s.vsbe)
		snम_लिखो(buf1, माप(buf1),
			 "type:%d, syn:0x%x, way:%d",
			 err_tdtx.s.type, err_tdtx.s.syn, err_tdtx.s.wayidx);

	अगर (err_tdtx.s.dbe) अणु
		snम_लिखो(buf2, माप(buf2),
			 "L2D Double bit error (detected):%s", buf1);
		err_tdtx_reset.s.dbe = 1;
		edac_device_handle_ue(l2c, tad, 1, buf2);
	पूर्ण
	अगर (err_tdtx.s.sbe) अणु
		snम_लिखो(buf2, माप(buf2),
			 "L2D Single bit error (corrected):%s", buf1);
		err_tdtx_reset.s.sbe = 1;
		edac_device_handle_ce(l2c, tad, 1, buf2);
	पूर्ण
	अगर (err_tdtx.s.vdbe) अणु
		snम_लिखो(buf2, माप(buf2),
			 "VBF Double bit error (detected):%s", buf1);
		err_tdtx_reset.s.vdbe = 1;
		edac_device_handle_ue(l2c, tad, 1, buf2);
	पूर्ण
	अगर (err_tdtx.s.vsbe) अणु
		snम_लिखो(buf2, माप(buf2),
			 "VBF Single bit error (corrected):%s", buf1);
		err_tdtx_reset.s.vsbe = 1;
		edac_device_handle_ce(l2c, tad, 1, buf2);
	पूर्ण
	अगर (err_tdtx_reset.u64)
		cvmx_ग_लिखो_csr(CVMX_L2C_ERR_TDTX(tad), err_tdtx_reset.u64);

	err_ttgx_reset.u64 = 0;
	err_ttgx.u64 = cvmx_पढ़ो_csr(CVMX_L2C_ERR_TTGX(tad));

	अगर (err_ttgx.s.dbe || err_ttgx.s.sbe)
		snम_लिखो(buf1, माप(buf1),
			 "type:%d, syn:0x%x, way:%d",
			 err_ttgx.s.type, err_ttgx.s.syn, err_ttgx.s.wayidx);

	अगर (err_ttgx.s.dbe) अणु
		snम_लिखो(buf2, माप(buf2),
			 "Tag Double bit error (detected):%s", buf1);
		err_ttgx_reset.s.dbe = 1;
		edac_device_handle_ue(l2c, tad, 0, buf2);
	पूर्ण
	अगर (err_ttgx.s.sbe) अणु
		snम_लिखो(buf2, माप(buf2),
			 "Tag Single bit error (corrected):%s", buf1);
		err_ttgx_reset.s.sbe = 1;
		edac_device_handle_ce(l2c, tad, 0, buf2);
	पूर्ण
	अगर (err_ttgx_reset.u64)
		cvmx_ग_लिखो_csr(CVMX_L2C_ERR_TTGX(tad), err_ttgx_reset.u64);
पूर्ण

अटल व्योम octeon_l2c_poll_oct2(काष्ठा edac_device_ctl_info *l2c)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < l2c->nr_instances; i++)
		_octeon_l2c_poll_oct2(l2c, i);
पूर्ण

अटल पूर्णांक octeon_l2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा edac_device_ctl_info *l2c;

	पूर्णांक num_tads = OCTEON_IS_MODEL(OCTEON_CN68XX) ? 4 : 1;

	/* 'Tags' are block 0, 'Data' is block 1*/
	l2c = edac_device_alloc_ctl_info(0, "l2c", num_tads, "l2c", 2, 0,
					 शून्य, 0, edac_device_alloc_index());
	अगर (!l2c)
		वापस -ENOMEM;

	l2c->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, l2c);
	l2c->dev_name = dev_name(&pdev->dev);

	l2c->mod_name = "octeon-l2c";
	l2c->ctl_name = "octeon_l2c_err";


	अगर (OCTEON_IS_OCTEON1PLUS()) अणु
		जोड़ cvmx_l2t_err l2t_err;
		जोड़ cvmx_l2d_err l2d_err;

		l2t_err.u64 = cvmx_पढ़ो_csr(CVMX_L2T_ERR);
		l2t_err.s.sec_पूर्णांकena = 0;	/* We poll */
		l2t_err.s.ded_पूर्णांकena = 0;
		cvmx_ग_लिखो_csr(CVMX_L2T_ERR, l2t_err.u64);

		l2d_err.u64 = cvmx_पढ़ो_csr(CVMX_L2D_ERR);
		l2d_err.s.sec_पूर्णांकena = 0;	/* We poll */
		l2d_err.s.ded_पूर्णांकena = 0;
		cvmx_ग_लिखो_csr(CVMX_L2T_ERR, l2d_err.u64);

		l2c->edac_check = octeon_l2c_poll_oct1;
	पूर्ण अन्यथा अणु
		/* OCTEON II */
		l2c->edac_check = octeon_l2c_poll_oct2;
	पूर्ण

	अगर (edac_device_add_device(l2c) > 0) अणु
		pr_err("%s: edac_device_add_device() failed\n", __func__);
		जाओ err;
	पूर्ण


	वापस 0;

err:
	edac_device_मुक्त_ctl_info(l2c);

	वापस -ENXIO;
पूर्ण

अटल पूर्णांक octeon_l2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा edac_device_ctl_info *l2c = platक्रमm_get_drvdata(pdev);

	edac_device_del_device(&pdev->dev);
	edac_device_मुक्त_ctl_info(l2c);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver octeon_l2c_driver = अणु
	.probe = octeon_l2c_probe,
	.हटाओ = octeon_l2c_हटाओ,
	.driver = अणु
		   .name = "octeon_l2c_edac",
	पूर्ण
पूर्ण;
module_platक्रमm_driver(octeon_l2c_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ralf Baechle <ralf@linux-mips.org>");
