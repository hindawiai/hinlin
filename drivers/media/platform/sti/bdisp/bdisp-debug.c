<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Authors: Fabien Dessenne <fabien.dessenne@st.com> क्रम STMicroelectronics.
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "bdisp.h"
#समावेश "bdisp-filter.h"
#समावेश "bdisp-reg.h"

व्योम bdisp_dbg_perf_begin(काष्ठा bdisp_dev *bdisp)
अणु
	bdisp->dbg.hw_start = kसमय_get();
पूर्ण

व्योम bdisp_dbg_perf_end(काष्ठा bdisp_dev *bdisp)
अणु
	s64 समय_us;

	समय_us = kसमय_us_delta(kसमय_get(), bdisp->dbg.hw_start);

	अगर (!bdisp->dbg.min_duration)
		bdisp->dbg.min_duration = समय_us;
	अन्यथा
		bdisp->dbg.min_duration = min(समय_us, bdisp->dbg.min_duration);

	bdisp->dbg.last_duration = समय_us;
	bdisp->dbg.max_duration = max(समय_us, bdisp->dbg.max_duration);
	bdisp->dbg.tot_duration += समय_us;
पूर्ण

अटल व्योम bdisp_dbg_dump_ins(काष्ठा seq_file *s, u32 val)
अणु
	seq_म_लिखो(s, "INS\t0x%08X\t", val);

	चयन (val & BLT_INS_S1_MASK) अणु
	हाल BLT_INS_S1_OFF:
		अवरोध;
	हाल BLT_INS_S1_MEM:
		seq_माला_दो(s, "SRC1=mem - ");
		अवरोध;
	हाल BLT_INS_S1_CF:
		seq_माला_दो(s, "SRC1=ColorFill - ");
		अवरोध;
	हाल BLT_INS_S1_COPY:
		seq_माला_दो(s, "SRC1=copy - ");
		अवरोध;
	हाल BLT_INS_S1_FILL:
		seq_माला_दो(s, "SRC1=fil - ");
		अवरोध;
	शेष:
		seq_माला_दो(s, "SRC1=??? - ");
		अवरोध;
	पूर्ण

	चयन (val & BLT_INS_S2_MASK) अणु
	हाल BLT_INS_S2_OFF:
		अवरोध;
	हाल BLT_INS_S2_MEM:
		seq_माला_दो(s, "SRC2=mem - ");
		अवरोध;
	हाल BLT_INS_S2_CF:
		seq_माला_दो(s, "SRC2=ColorFill - ");
		अवरोध;
	शेष:
		seq_माला_दो(s, "SRC2=??? - ");
		अवरोध;
	पूर्ण

	अगर ((val & BLT_INS_S3_MASK) == BLT_INS_S3_MEM)
		seq_माला_दो(s, "SRC3=mem - ");

	अगर (val & BLT_INS_IVMX)
		seq_माला_दो(s, "IVMX - ");
	अगर (val & BLT_INS_CLUT)
		seq_माला_दो(s, "CLUT - ");
	अगर (val & BLT_INS_SCALE)
		seq_माला_दो(s, "Scale - ");
	अगर (val & BLT_INS_FLICK)
		seq_माला_दो(s, "Flicker - ");
	अगर (val & BLT_INS_CLIP)
		seq_माला_दो(s, "Clip - ");
	अगर (val & BLT_INS_CKEY)
		seq_माला_दो(s, "ColorKey - ");
	अगर (val & BLT_INS_OVMX)
		seq_माला_दो(s, "OVMX - ");
	अगर (val & BLT_INS_DEI)
		seq_माला_दो(s, "Deint - ");
	अगर (val & BLT_INS_PMASK)
		seq_माला_दो(s, "PlaneMask - ");
	अगर (val & BLT_INS_VC1R)
		seq_माला_दो(s, "VC1R - ");
	अगर (val & BLT_INS_ROTATE)
		seq_माला_दो(s, "Rotate - ");
	अगर (val & BLT_INS_GRAD)
		seq_माला_दो(s, "GradFill - ");
	अगर (val & BLT_INS_AQLOCK)
		seq_माला_दो(s, "AQLock - ");
	अगर (val & BLT_INS_PACE)
		seq_माला_दो(s, "Pace - ");
	अगर (val & BLT_INS_IRQ)
		seq_माला_दो(s, "IRQ - ");

	seq_अ_दो(s, '\n');
पूर्ण

अटल व्योम bdisp_dbg_dump_tty(काष्ठा seq_file *s, u32 val)
अणु
	seq_म_लिखो(s, "TTY\t0x%08X\t", val);
	seq_म_लिखो(s, "Pitch=%d - ", val & 0xFFFF);

	चयन ((val & BLT_TTY_COL_MASK) >> BLT_TTY_COL_SHIFT) अणु
	हाल BDISP_RGB565:
		seq_माला_दो(s, "RGB565 - ");
		अवरोध;
	हाल BDISP_RGB888:
		seq_माला_दो(s, "RGB888 - ");
		अवरोध;
	हाल BDISP_XRGB8888:
		seq_माला_दो(s, "xRGB888 - ");
		अवरोध;
	हाल BDISP_ARGB8888:
		seq_माला_दो(s, "ARGB8888 - ");
		अवरोध;
	हाल BDISP_NV12:
		seq_माला_दो(s, "NV12 - ");
		अवरोध;
	हाल BDISP_YUV_3B:
		seq_माला_दो(s, "YUV420P - ");
		अवरोध;
	शेष:
		seq_माला_दो(s, "ColorFormat ??? - ");
		अवरोध;
	पूर्ण

	अगर (val & BLT_TTY_ALPHA_R)
		seq_माला_दो(s, "AlphaRange - ");
	अगर (val & BLT_TTY_CR_NOT_CB)
		seq_माला_दो(s, "CrNotCb - ");
	अगर (val & BLT_TTY_MB)
		seq_माला_दो(s, "MB - ");
	अगर (val & BLT_TTY_HSO)
		seq_माला_दो(s, "HSO inverse - ");
	अगर (val & BLT_TTY_VSO)
		seq_माला_दो(s, "VSO inverse - ");
	अगर (val & BLT_TTY_DITHER)
		seq_माला_दो(s, "Dither - ");
	अगर (val & BLT_TTY_CHROMA)
		seq_माला_दो(s, "Write CHROMA - ");
	अगर (val & BLT_TTY_BIG_END)
		seq_माला_दो(s, "BigEndian - ");

	seq_अ_दो(s, '\n');
पूर्ण

अटल व्योम bdisp_dbg_dump_xy(काष्ठा seq_file *s, u32 val, अक्षर *name)
अणु
	seq_म_लिखो(s, "%s\t0x%08X\t", name, val);
	seq_म_लिखो(s, "(%d,%d)\n", val & 0xFFFF, (val >> 16));
पूर्ण

अटल व्योम bdisp_dbg_dump_sz(काष्ठा seq_file *s, u32 val, अक्षर *name)
अणु
	seq_म_लिखो(s, "%s\t0x%08X\t", name, val);
	seq_म_लिखो(s, "%dx%d\n", val & 0x1FFF, (val >> 16) & 0x1FFF);
पूर्ण

अटल व्योम bdisp_dbg_dump_sty(काष्ठा seq_file *s,
			       u32 val, u32 addr, अक्षर *name)
अणु
	bool s1, s2, s3;

	seq_म_लिखो(s, "%s\t0x%08X\t", name, val);

	अगर (!addr || !name || (म_माप(name) < 2))
		जाओ करोne;

	s1 = name[म_माप(name) - 1] == '1';
	s2 = name[म_माप(name) - 1] == '2';
	s3 = name[म_माप(name) - 1] == '3';

	seq_म_लिखो(s, "Pitch=%d - ", val & 0xFFFF);

	चयन ((val & BLT_TTY_COL_MASK) >> BLT_TTY_COL_SHIFT) अणु
	हाल BDISP_RGB565:
		seq_माला_दो(s, "RGB565 - ");
		अवरोध;
	हाल BDISP_RGB888:
		seq_माला_दो(s, "RGB888 - ");
		अवरोध;
	हाल BDISP_XRGB8888:
		seq_माला_दो(s, "xRGB888 - ");
		अवरोध;
	हाल BDISP_ARGB8888:
		seq_माला_दो(s, "ARGB888 - ");
		अवरोध;
	हाल BDISP_NV12:
		seq_माला_दो(s, "NV12 - ");
		अवरोध;
	हाल BDISP_YUV_3B:
		seq_माला_दो(s, "YUV420P - ");
		अवरोध;
	शेष:
		seq_माला_दो(s, "ColorFormat ??? - ");
		अवरोध;
	पूर्ण

	अगर ((val & BLT_TTY_ALPHA_R) && !s3)
		seq_माला_दो(s, "AlphaRange - ");
	अगर ((val & BLT_S1TY_A1_SUBSET) && !s3)
		seq_माला_दो(s, "A1SubSet - ");
	अगर ((val & BLT_TTY_MB) && !s1)
		seq_माला_दो(s, "MB - ");
	अगर (val & BLT_TTY_HSO)
		seq_माला_दो(s, "HSO inverse - ");
	अगर (val & BLT_TTY_VSO)
		seq_माला_दो(s, "VSO inverse - ");
	अगर ((val & BLT_S1TY_CHROMA_EXT) && (s1 || s2))
		seq_माला_दो(s, "ChromaExt - ");
	अगर ((val & BLT_S3TY_BLANK_ACC) && s3)
		seq_माला_दो(s, "Blank Acc - ");
	अगर ((val & BTL_S1TY_SUBBYTE) && !s3)
		seq_माला_दो(s, "SubByte - ");
	अगर ((val & BLT_S1TY_RGB_EXP) && !s3)
		seq_माला_दो(s, "RGBExpand - ");
	अगर ((val & BLT_TTY_BIG_END) && !s3)
		seq_माला_दो(s, "BigEndian - ");

करोne:
	seq_अ_दो(s, '\n');
पूर्ण

अटल व्योम bdisp_dbg_dump_fctl(काष्ठा seq_file *s, u32 val)
अणु
	seq_म_लिखो(s, "FCTL\t0x%08X\t", val);

	अगर ((val & BLT_FCTL_Y_HV_SCALE) == BLT_FCTL_Y_HV_SCALE)
		seq_माला_दो(s, "Resize Luma - ");
	अन्यथा अगर ((val & BLT_FCTL_Y_HV_SCALE) == BLT_FCTL_Y_HV_SAMPLE)
		seq_माला_दो(s, "Sample Luma - ");

	अगर ((val & BLT_FCTL_HV_SCALE) == BLT_FCTL_HV_SCALE)
		seq_माला_दो(s, "Resize Chroma");
	अन्यथा अगर ((val & BLT_FCTL_HV_SCALE) == BLT_FCTL_HV_SAMPLE)
		seq_माला_दो(s, "Sample Chroma");

	seq_अ_दो(s, '\n');
पूर्ण

अटल व्योम bdisp_dbg_dump_rsf(काष्ठा seq_file *s, u32 val, अक्षर *name)
अणु
	u32 inc;

	seq_म_लिखो(s, "%s\t0x%08X\t", name, val);

	अगर (!val)
		जाओ करोne;

	inc = val & 0xFFFF;
	seq_म_लिखो(s, "H: %d(6.10) / scale~%dx0.1 - ", inc, 1024 * 10 / inc);

	inc = val >> 16;
	seq_म_लिखो(s, "V: %d(6.10) / scale~%dx0.1", inc, 1024 * 10 / inc);

करोne:
	seq_अ_दो(s, '\n');
पूर्ण

अटल व्योम bdisp_dbg_dump_rzi(काष्ठा seq_file *s, u32 val, अक्षर *name)
अणु
	seq_म_लिखो(s, "%s\t0x%08X\t", name, val);

	अगर (!val)
		जाओ करोne;

	seq_म_लिखो(s, "H: init=%d repeat=%d - ", val & 0x3FF, (val >> 12) & 7);
	val >>= 16;
	seq_म_लिखो(s, "V: init=%d repeat=%d", val & 0x3FF, (val >> 12) & 7);

करोne:
	seq_अ_दो(s, '\n');
पूर्ण

अटल व्योम bdisp_dbg_dump_ivmx(काष्ठा seq_file *s,
				u32 c0, u32 c1, u32 c2, u32 c3)
अणु
	seq_म_लिखो(s, "IVMX0\t0x%08X\n", c0);
	seq_म_लिखो(s, "IVMX1\t0x%08X\n", c1);
	seq_म_लिखो(s, "IVMX2\t0x%08X\n", c2);
	seq_म_लिखो(s, "IVMX3\t0x%08X\t", c3);

	अगर (!c0 && !c1 && !c2 && !c3) अणु
		seq_अ_दो(s, '\n');
		वापस;
	पूर्ण

	अगर ((c0 == bdisp_rgb_to_yuv[0]) &&
	    (c1 == bdisp_rgb_to_yuv[1]) &&
	    (c2 == bdisp_rgb_to_yuv[2]) &&
	    (c3 == bdisp_rgb_to_yuv[3])) अणु
		seq_माला_दो(s, "RGB to YUV\n");
		वापस;
	पूर्ण

	अगर ((c0 == bdisp_yuv_to_rgb[0]) &&
	    (c1 == bdisp_yuv_to_rgb[1]) &&
	    (c2 == bdisp_yuv_to_rgb[2]) &&
	    (c3 == bdisp_yuv_to_rgb[3])) अणु
		seq_माला_दो(s, "YUV to RGB\n");
		वापस;
	पूर्ण
	seq_माला_दो(s, "Unknown conversion\n");
पूर्ण

अटल पूर्णांक last_nodes_show(काष्ठा seq_file *s, व्योम *data)
अणु
	/* Not dumping all fields, focusing on signअगरicant ones */
	काष्ठा bdisp_dev *bdisp = s->निजी;
	काष्ठा bdisp_node *node;
	पूर्णांक i = 0;

	अगर (!bdisp->dbg.copy_node[0]) अणु
		seq_माला_दो(s, "No node built yet\n");
		वापस 0;
	पूर्ण

	करो अणु
		node = bdisp->dbg.copy_node[i];
		अगर (!node)
			अवरोध;
		seq_म_लिखो(s, "--------\nNode %d:\n", i);
		seq_माला_दो(s, "-- General --\n");
		seq_म_लिखो(s, "NIP\t0x%08X\n", node->nip);
		seq_म_लिखो(s, "CIC\t0x%08X\n", node->cic);
		bdisp_dbg_dump_ins(s, node->ins);
		seq_म_लिखो(s, "ACK\t0x%08X\n", node->ack);
		seq_माला_दो(s, "-- Target --\n");
		seq_म_लिखो(s, "TBA\t0x%08X\n", node->tba);
		bdisp_dbg_dump_tty(s, node->tty);
		bdisp_dbg_dump_xy(s, node->txy, "TXY");
		bdisp_dbg_dump_sz(s, node->tsz, "TSZ");
		/* Color Fill not dumped */
		seq_माला_दो(s, "-- Source 1 --\n");
		seq_म_लिखो(s, "S1BA\t0x%08X\n", node->s1ba);
		bdisp_dbg_dump_sty(s, node->s1ty, node->s1ba, "S1TY");
		bdisp_dbg_dump_xy(s, node->s1xy, "S1XY");
		seq_माला_दो(s, "-- Source 2 --\n");
		seq_म_लिखो(s, "S2BA\t0x%08X\n", node->s2ba);
		bdisp_dbg_dump_sty(s, node->s2ty, node->s2ba, "S2TY");
		bdisp_dbg_dump_xy(s, node->s2xy, "S2XY");
		bdisp_dbg_dump_sz(s, node->s2sz, "S2SZ");
		seq_माला_दो(s, "-- Source 3 --\n");
		seq_म_लिखो(s, "S3BA\t0x%08X\n", node->s3ba);
		bdisp_dbg_dump_sty(s, node->s3ty, node->s3ba, "S3TY");
		bdisp_dbg_dump_xy(s, node->s3xy, "S3XY");
		bdisp_dbg_dump_sz(s, node->s3sz, "S3SZ");
		/* Clipping not dumped */
		/* CLUT not dumped */
		seq_माला_दो(s, "-- Filter & Mask --\n");
		bdisp_dbg_dump_fctl(s, node->fctl);
		/* PMK not dumped */
		seq_माला_दो(s, "-- Chroma Filter --\n");
		bdisp_dbg_dump_rsf(s, node->rsf, "RSF");
		bdisp_dbg_dump_rzi(s, node->rzi, "RZI");
		seq_म_लिखो(s, "HFP\t0x%08X\n", node->hfp);
		seq_म_लिखो(s, "VFP\t0x%08X\n", node->vfp);
		seq_माला_दो(s, "-- Luma Filter --\n");
		bdisp_dbg_dump_rsf(s, node->y_rsf, "Y_RSF");
		bdisp_dbg_dump_rzi(s, node->y_rzi, "Y_RZI");
		seq_म_लिखो(s, "Y_HFP\t0x%08X\n", node->y_hfp);
		seq_म_लिखो(s, "Y_VFP\t0x%08X\n", node->y_vfp);
		/* Flicker not dumped */
		/* Color key not dumped */
		/* Reserved not dumped */
		/* Static Address & User not dumped */
		seq_माला_दो(s, "-- Input Versatile Matrix --\n");
		bdisp_dbg_dump_ivmx(s, node->ivmx0, node->ivmx1,
				    node->ivmx2, node->ivmx3);
		/* Output Versatile Matrix not dumped */
		/* Pace not dumped */
		/* VC1R & DEI not dumped */
		/* Gradient Fill not dumped */
	पूर्ण जबतक ((++i < MAX_NB_NODE) && node->nip);

	वापस 0;
पूर्ण

अटल पूर्णांक last_nodes_raw_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा bdisp_dev *bdisp = s->निजी;
	काष्ठा bdisp_node *node;
	u32 *val;
	पूर्णांक j, i = 0;

	अगर (!bdisp->dbg.copy_node[0]) अणु
		seq_माला_दो(s, "No node built yet\n");
		वापस 0;
	पूर्ण

	करो अणु
		node = bdisp->dbg.copy_node[i];
		अगर (!node)
			अवरोध;

		seq_म_लिखो(s, "--------\nNode %d:\n", i);
		val = (u32 *)node;
		क्रम (j = 0; j < माप(काष्ठा bdisp_node) / माप(u32); j++)
			seq_म_लिखो(s, "0x%08X\n", *val++);
	पूर्ण जबतक ((++i < MAX_NB_NODE) && node->nip);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *bdisp_fmt_to_str(काष्ठा bdisp_frame frame)
अणु
	चयन (frame.fmt->pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_YUV420:
		वापस "YUV420P";
	हाल V4L2_PIX_FMT_NV12:
		अगर (frame.field == V4L2_FIELD_INTERLACED)
			वापस "NV12 interlaced";
		अन्यथा
			वापस "NV12";
	हाल V4L2_PIX_FMT_RGB565:
		वापस "RGB16";
	हाल V4L2_PIX_FMT_RGB24:
		वापस "RGB24";
	हाल V4L2_PIX_FMT_XBGR32:
		वापस "XRGB";
	हाल V4L2_PIX_FMT_ABGR32:
		वापस "ARGB";
	शेष:
		वापस "????";
	पूर्ण
पूर्ण

अटल पूर्णांक last_request_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा bdisp_dev *bdisp = s->निजी;
	काष्ठा bdisp_request *request = &bdisp->dbg.copy_request;
	काष्ठा bdisp_frame src, dst;

	अगर (!request->nb_req) अणु
		seq_माला_दो(s, "No request\n");
		वापस 0;
	पूर्ण

	src = request->src;
	dst = request->dst;

	seq_म_लिखो(s, "\nRequest #%d\n", request->nb_req);

	seq_म_लिखो(s, "Format:    %s\t\t\t%s\n",
		   bdisp_fmt_to_str(src), bdisp_fmt_to_str(dst));
	seq_म_लिखो(s, "Crop area: %dx%d @ %d,%d  ==>\t%dx%d @ %d,%d\n",
		   src.crop.width, src.crop.height,
		   src.crop.left, src.crop.top,
		   dst.crop.width, dst.crop.height,
		   dst.crop.left, dst.crop.top);
	seq_म_लिखो(s, "Buff size: %dx%d\t\t%dx%d\n\n",
		   src.width, src.height, dst.width, dst.height);

	अगर (request->hflip)
		seq_माला_दो(s, "Horizontal flip\n\n");

	अगर (request->vflip)
		seq_माला_दो(s, "Vertical flip\n\n");

	वापस 0;
पूर्ण

#घोषणा DUMP(reg) seq_म_लिखो(s, #reg " \t0x%08X\n", पढ़ोl(bdisp->regs + reg))

अटल पूर्णांक regs_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा bdisp_dev *bdisp = s->निजी;
	पूर्णांक ret;
	अचिन्हित पूर्णांक i;

	ret = pm_runसमय_resume_and_get(bdisp->dev);
	अगर (ret < 0) अणु
		seq_माला_दो(s, "Cannot wake up IP\n");
		वापस 0;
	पूर्ण

	seq_म_लिखो(s, "Reg @ = 0x%p\n", bdisp->regs);

	seq_माला_दो(s, "\nStatic:\n");
	DUMP(BLT_CTL);
	DUMP(BLT_ITS);
	DUMP(BLT_STA1);
	DUMP(BLT_AQ1_CTL);
	DUMP(BLT_AQ1_IP);
	DUMP(BLT_AQ1_LNA);
	DUMP(BLT_AQ1_STA);
	DUMP(BLT_ITM0);

	seq_माला_दो(s, "\nPlugs:\n");
	DUMP(BLT_PLUGS1_OP2);
	DUMP(BLT_PLUGS1_CHZ);
	DUMP(BLT_PLUGS1_MSZ);
	DUMP(BLT_PLUGS1_PGZ);
	DUMP(BLT_PLUGS2_OP2);
	DUMP(BLT_PLUGS2_CHZ);
	DUMP(BLT_PLUGS2_MSZ);
	DUMP(BLT_PLUGS2_PGZ);
	DUMP(BLT_PLUGS3_OP2);
	DUMP(BLT_PLUGS3_CHZ);
	DUMP(BLT_PLUGS3_MSZ);
	DUMP(BLT_PLUGS3_PGZ);
	DUMP(BLT_PLUGT_OP2);
	DUMP(BLT_PLUGT_CHZ);
	DUMP(BLT_PLUGT_MSZ);
	DUMP(BLT_PLUGT_PGZ);

	seq_माला_दो(s, "\nNode:\n");
	DUMP(BLT_NIP);
	DUMP(BLT_CIC);
	DUMP(BLT_INS);
	DUMP(BLT_ACK);
	DUMP(BLT_TBA);
	DUMP(BLT_TTY);
	DUMP(BLT_TXY);
	DUMP(BLT_TSZ);
	DUMP(BLT_S1BA);
	DUMP(BLT_S1TY);
	DUMP(BLT_S1XY);
	DUMP(BLT_S2BA);
	DUMP(BLT_S2TY);
	DUMP(BLT_S2XY);
	DUMP(BLT_S2SZ);
	DUMP(BLT_S3BA);
	DUMP(BLT_S3TY);
	DUMP(BLT_S3XY);
	DUMP(BLT_S3SZ);
	DUMP(BLT_FCTL);
	DUMP(BLT_RSF);
	DUMP(BLT_RZI);
	DUMP(BLT_HFP);
	DUMP(BLT_VFP);
	DUMP(BLT_Y_RSF);
	DUMP(BLT_Y_RZI);
	DUMP(BLT_Y_HFP);
	DUMP(BLT_Y_VFP);
	DUMP(BLT_IVMX0);
	DUMP(BLT_IVMX1);
	DUMP(BLT_IVMX2);
	DUMP(BLT_IVMX3);
	DUMP(BLT_OVMX0);
	DUMP(BLT_OVMX1);
	DUMP(BLT_OVMX2);
	DUMP(BLT_OVMX3);
	DUMP(BLT_DEI);

	seq_माला_दो(s, "\nFilter:\n");
	क्रम (i = 0; i < BLT_NB_H_COEF; i++) अणु
		seq_म_लिखो(s, "BLT_HFC%d \t0x%08X\n", i,
			   पढ़ोl(bdisp->regs + BLT_HFC_N + i * 4));
	पूर्ण
	क्रम (i = 0; i < BLT_NB_V_COEF; i++) अणु
		seq_म_लिखो(s, "BLT_VFC%d \t0x%08X\n", i,
			   पढ़ोl(bdisp->regs + BLT_VFC_N + i * 4));
	पूर्ण

	seq_माला_दो(s, "\nLuma filter:\n");
	क्रम (i = 0; i < BLT_NB_H_COEF; i++) अणु
		seq_म_लिखो(s, "BLT_Y_HFC%d \t0x%08X\n", i,
			   पढ़ोl(bdisp->regs + BLT_Y_HFC_N + i * 4));
	पूर्ण
	क्रम (i = 0; i < BLT_NB_V_COEF; i++) अणु
		seq_म_लिखो(s, "BLT_Y_VFC%d \t0x%08X\n", i,
			   पढ़ोl(bdisp->regs + BLT_Y_VFC_N + i * 4));
	पूर्ण

	pm_runसमय_put(bdisp->dev);

	वापस 0;
पूर्ण

#घोषणा SECOND 1000000

अटल पूर्णांक perf_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा bdisp_dev *bdisp = s->निजी;
	काष्ठा bdisp_request *request = &bdisp->dbg.copy_request;
	s64 avg_समय_us;
	पूर्णांक avg_fps, min_fps, max_fps, last_fps;

	अगर (!request->nb_req) अणु
		seq_माला_दो(s, "No request\n");
		वापस 0;
	पूर्ण

	avg_समय_us = भाग64_s64(bdisp->dbg.tot_duration, request->nb_req);
	अगर (avg_समय_us > SECOND)
		avg_fps = 0;
	अन्यथा
		avg_fps = SECOND / (s32)avg_समय_us;

	अगर (bdisp->dbg.min_duration > SECOND)
		min_fps = 0;
	अन्यथा
		min_fps = SECOND / (s32)bdisp->dbg.min_duration;

	अगर (bdisp->dbg.max_duration > SECOND)
		max_fps = 0;
	अन्यथा
		max_fps = SECOND / (s32)bdisp->dbg.max_duration;

	अगर (bdisp->dbg.last_duration > SECOND)
		last_fps = 0;
	अन्यथा
		last_fps = SECOND / (s32)bdisp->dbg.last_duration;

	seq_म_लिखो(s, "HW processing (%d requests):\n", request->nb_req);
	seq_म_लिखो(s, " Average: %5lld us  (%3d fps)\n",
		   avg_समय_us, avg_fps);
	seq_म_लिखो(s, " Min-Max: %5lld us  (%3d fps) - %5lld us  (%3d fps)\n",
		   bdisp->dbg.min_duration, min_fps,
		   bdisp->dbg.max_duration, max_fps);
	seq_म_लिखो(s, " Last:    %5lld us  (%3d fps)\n",
		   bdisp->dbg.last_duration, last_fps);

	वापस 0;
पूर्ण

#घोषणा bdisp_dbg_create_entry(name) \
	debugfs_create_file(#name, S_IRUGO, bdisp->dbg.debugfs_entry, bdisp, \
			    &name##_fops)

DEFINE_SHOW_ATTRIBUTE(regs);
DEFINE_SHOW_ATTRIBUTE(last_nodes);
DEFINE_SHOW_ATTRIBUTE(last_nodes_raw);
DEFINE_SHOW_ATTRIBUTE(last_request);
DEFINE_SHOW_ATTRIBUTE(perf);

व्योम bdisp_debugfs_create(काष्ठा bdisp_dev *bdisp)
अणु
	अक्षर स_नाम[16];

	snम_लिखो(स_नाम, माप(स_नाम), "%s%d", BDISP_NAME, bdisp->id);
	bdisp->dbg.debugfs_entry = debugfs_create_dir(स_नाम, शून्य);

	bdisp_dbg_create_entry(regs);
	bdisp_dbg_create_entry(last_nodes);
	bdisp_dbg_create_entry(last_nodes_raw);
	bdisp_dbg_create_entry(last_request);
	bdisp_dbg_create_entry(perf);
पूर्ण

व्योम bdisp_debugfs_हटाओ(काष्ठा bdisp_dev *bdisp)
अणु
	debugfs_हटाओ_recursive(bdisp->dbg.debugfs_entry);
	bdisp->dbg.debugfs_entry = शून्य;
पूर्ण
