<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Video capture पूर्णांकerface क्रम Linux version 2
 *
 * A generic framework to process V4L2 ioctl commands.
 *
 * Authors:	Alan Cox, <alan@lxorguk.ukuu.org.uk> (version 1)
 *              Mauro Carvalho Chehab <mchehab@kernel.org> (version 2)
 */

#समावेश <linux/compat.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/version.h>

#समावेश <linux/videodev2.h>

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/v4l2-mc.h>
#समावेश <media/v4l2-mem2स्मृति.स>

#समावेश <trace/events/v4l2.h>

/* Zero out the end of the काष्ठा poपूर्णांकed to by p.  Everything after, but
 * not including, the specअगरied field is cleared. */
#घोषणा CLEAR_AFTER_FIELD(p, field) \
	स_रखो((u8 *)(p) + दुरत्व(typeof(*(p)), field) + माप((p)->field), \
	0, माप(*(p)) - दुरत्व(typeof(*(p)), field) - माप((p)->field))

#घोषणा is_valid_ioctl(vfd, cmd) test_bit(_IOC_NR(cmd), (vfd)->valid_ioctls)

काष्ठा std_descr अणु
	v4l2_std_id std;
	स्थिर अक्षर *descr;
पूर्ण;

अटल स्थिर काष्ठा std_descr standards[] = अणु
	अणु V4L2_STD_NTSC,	"NTSC"      पूर्ण,
	अणु V4L2_STD_NTSC_M,	"NTSC-M"    पूर्ण,
	अणु V4L2_STD_NTSC_M_JP,	"NTSC-M-JP" पूर्ण,
	अणु V4L2_STD_NTSC_M_KR,	"NTSC-M-KR" पूर्ण,
	अणु V4L2_STD_NTSC_443,	"NTSC-443"  पूर्ण,
	अणु V4L2_STD_PAL,		"PAL"       पूर्ण,
	अणु V4L2_STD_PAL_BG,	"PAL-BG"    पूर्ण,
	अणु V4L2_STD_PAL_B,	"PAL-B"     पूर्ण,
	अणु V4L2_STD_PAL_B1,	"PAL-B1"    पूर्ण,
	अणु V4L2_STD_PAL_G,	"PAL-G"     पूर्ण,
	अणु V4L2_STD_PAL_H,	"PAL-H"     पूर्ण,
	अणु V4L2_STD_PAL_I,	"PAL-I"     पूर्ण,
	अणु V4L2_STD_PAL_DK,	"PAL-DK"    पूर्ण,
	अणु V4L2_STD_PAL_D,	"PAL-D"     पूर्ण,
	अणु V4L2_STD_PAL_D1,	"PAL-D1"    पूर्ण,
	अणु V4L2_STD_PAL_K,	"PAL-K"     पूर्ण,
	अणु V4L2_STD_PAL_M,	"PAL-M"     पूर्ण,
	अणु V4L2_STD_PAL_N,	"PAL-N"     पूर्ण,
	अणु V4L2_STD_PAL_Nc,	"PAL-Nc"    पूर्ण,
	अणु V4L2_STD_PAL_60,	"PAL-60"    पूर्ण,
	अणु V4L2_STD_SECAM,	"SECAM"     पूर्ण,
	अणु V4L2_STD_SECAM_B,	"SECAM-B"   पूर्ण,
	अणु V4L2_STD_SECAM_G,	"SECAM-G"   पूर्ण,
	अणु V4L2_STD_SECAM_H,	"SECAM-H"   पूर्ण,
	अणु V4L2_STD_SECAM_DK,	"SECAM-DK"  पूर्ण,
	अणु V4L2_STD_SECAM_D,	"SECAM-D"   पूर्ण,
	अणु V4L2_STD_SECAM_K,	"SECAM-K"   पूर्ण,
	अणु V4L2_STD_SECAM_K1,	"SECAM-K1"  पूर्ण,
	अणु V4L2_STD_SECAM_L,	"SECAM-L"   पूर्ण,
	अणु V4L2_STD_SECAM_LC,	"SECAM-Lc"  पूर्ण,
	अणु 0,			"Unknown"   पूर्ण
पूर्ण;

/* video4linux standard ID conversion to standard name
 */
स्थिर अक्षर *v4l2_norm_to_name(v4l2_std_id id)
अणु
	u32 myid = id;
	पूर्णांक i;

	/* HACK: ppc32 architecture करोesn't have __ucmpdi2 function to handle
	   64 bit comparisons. So, on that architecture, with some gcc
	   variants, compilation fails. Currently, the max value is 30bit wide.
	 */
	BUG_ON(myid != id);

	क्रम (i = 0; standards[i].std; i++)
		अगर (myid == standards[i].std)
			अवरोध;
	वापस standards[i].descr;
पूर्ण
EXPORT_SYMBOL(v4l2_norm_to_name);

/* Returns frame period क्रम the given standard */
व्योम v4l2_video_std_frame_period(पूर्णांक id, काष्ठा v4l2_fract *frameperiod)
अणु
	अगर (id & V4L2_STD_525_60) अणु
		frameperiod->numerator = 1001;
		frameperiod->denominator = 30000;
	पूर्ण अन्यथा अणु
		frameperiod->numerator = 1;
		frameperiod->denominator = 25;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(v4l2_video_std_frame_period);

/* Fill in the fields of a v4l2_standard काष्ठाure according to the
   'id' and 'transmission' parameters.  Returns negative on error.  */
पूर्णांक v4l2_video_std_स्थिरruct(काष्ठा v4l2_standard *vs,
			     पूर्णांक id, स्थिर अक्षर *name)
अणु
	vs->id = id;
	v4l2_video_std_frame_period(id, &vs->frameperiod);
	vs->framelines = (id & V4L2_STD_525_60) ? 525 : 625;
	strscpy(vs->name, name, माप(vs->name));
	वापस 0;
पूर्ण
EXPORT_SYMBOL(v4l2_video_std_स्थिरruct);

/* Fill in the fields of a v4l2_standard काष्ठाure according to the
 * 'id' and 'vs->index' parameters. Returns negative on error. */
पूर्णांक v4l_video_std_क्रमागतstd(काष्ठा v4l2_standard *vs, v4l2_std_id id)
अणु
	v4l2_std_id curr_id = 0;
	अचिन्हित पूर्णांक index = vs->index, i, j = 0;
	स्थिर अक्षर *descr = "";

	/* Return -ENODATA अगर the id क्रम the current input
	   or output is 0, meaning that it करोesn't support this API. */
	अगर (id == 0)
		वापस -ENODATA;

	/* Return norm array in a canonical way */
	क्रम (i = 0; i <= index && id; i++) अणु
		/* last std value in the standards array is 0, so this
		   जबतक always ends there since (id & 0) == 0. */
		जबतक ((id & standards[j].std) != standards[j].std)
			j++;
		curr_id = standards[j].std;
		descr = standards[j].descr;
		j++;
		अगर (curr_id == 0)
			अवरोध;
		अगर (curr_id != V4L2_STD_PAL &&
				curr_id != V4L2_STD_SECAM &&
				curr_id != V4L2_STD_NTSC)
			id &= ~curr_id;
	पूर्ण
	अगर (i <= index)
		वापस -EINVAL;

	v4l2_video_std_स्थिरruct(vs, curr_id, descr);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------- */
/* some arrays क्रम pretty-prपूर्णांकing debug messages of क्रमागत types      */

स्थिर अक्षर *v4l2_field_names[] = अणु
	[V4L2_FIELD_ANY]        = "any",
	[V4L2_FIELD_NONE]       = "none",
	[V4L2_FIELD_TOP]        = "top",
	[V4L2_FIELD_BOTTOM]     = "bottom",
	[V4L2_FIELD_INTERLACED] = "interlaced",
	[V4L2_FIELD_SEQ_TB]     = "seq-tb",
	[V4L2_FIELD_SEQ_BT]     = "seq-bt",
	[V4L2_FIELD_ALTERNATE]  = "alternate",
	[V4L2_FIELD_INTERLACED_TB] = "interlaced-tb",
	[V4L2_FIELD_INTERLACED_BT] = "interlaced-bt",
पूर्ण;
EXPORT_SYMBOL(v4l2_field_names);

स्थिर अक्षर *v4l2_type_names[] = अणु
	[0]				   = "0",
	[V4L2_BUF_TYPE_VIDEO_CAPTURE]      = "vid-cap",
	[V4L2_BUF_TYPE_VIDEO_OVERLAY]      = "vid-overlay",
	[V4L2_BUF_TYPE_VIDEO_OUTPUT]       = "vid-out",
	[V4L2_BUF_TYPE_VBI_CAPTURE]        = "vbi-cap",
	[V4L2_BUF_TYPE_VBI_OUTPUT]         = "vbi-out",
	[V4L2_BUF_TYPE_SLICED_VBI_CAPTURE] = "sliced-vbi-cap",
	[V4L2_BUF_TYPE_SLICED_VBI_OUTPUT]  = "sliced-vbi-out",
	[V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY] = "vid-out-overlay",
	[V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE] = "vid-cap-mplane",
	[V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE] = "vid-out-mplane",
	[V4L2_BUF_TYPE_SDR_CAPTURE]        = "sdr-cap",
	[V4L2_BUF_TYPE_SDR_OUTPUT]         = "sdr-out",
	[V4L2_BUF_TYPE_META_CAPTURE]       = "meta-cap",
	[V4L2_BUF_TYPE_META_OUTPUT]	   = "meta-out",
पूर्ण;
EXPORT_SYMBOL(v4l2_type_names);

अटल स्थिर अक्षर *v4l2_memory_names[] = अणु
	[V4L2_MEMORY_MMAP]    = "mmap",
	[V4L2_MEMORY_USERPTR] = "userptr",
	[V4L2_MEMORY_OVERLAY] = "overlay",
	[V4L2_MEMORY_DMABUF] = "dmabuf",
पूर्ण;

#घोषणा prt_names(a, arr) (((अचिन्हित)(a)) < ARRAY_SIZE(arr) ? arr[a] : "unknown")

/* ------------------------------------------------------------------ */
/* debug help functions                                               */

अटल व्योम v4l_prपूर्णांक_querycap(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_capability *p = arg;

	pr_cont("driver=%.*s, card=%.*s, bus=%.*s, version=0x%08x, capabilities=0x%08x, device_caps=0x%08x\n",
		(पूर्णांक)माप(p->driver), p->driver,
		(पूर्णांक)माप(p->card), p->card,
		(पूर्णांक)माप(p->bus_info), p->bus_info,
		p->version, p->capabilities, p->device_caps);
पूर्ण

अटल व्योम v4l_prपूर्णांक_क्रमागतinput(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_input *p = arg;

	pr_cont("index=%u, name=%.*s, type=%u, audioset=0x%x, tuner=%u, std=0x%08Lx, status=0x%x, capabilities=0x%x\n",
		p->index, (पूर्णांक)माप(p->name), p->name, p->type, p->audioset,
		p->tuner, (अचिन्हित दीर्घ दीर्घ)p->std, p->status,
		p->capabilities);
पूर्ण

अटल व्योम v4l_prपूर्णांक_क्रमागतoutput(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_output *p = arg;

	pr_cont("index=%u, name=%.*s, type=%u, audioset=0x%x, modulator=%u, std=0x%08Lx, capabilities=0x%x\n",
		p->index, (पूर्णांक)माप(p->name), p->name, p->type, p->audioset,
		p->modulator, (अचिन्हित दीर्घ दीर्घ)p->std, p->capabilities);
पूर्ण

अटल व्योम v4l_prपूर्णांक_audio(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_audio *p = arg;

	अगर (ग_लिखो_only)
		pr_cont("index=%u, mode=0x%x\n", p->index, p->mode);
	अन्यथा
		pr_cont("index=%u, name=%.*s, capability=0x%x, mode=0x%x\n",
			p->index, (पूर्णांक)माप(p->name), p->name,
			p->capability, p->mode);
पूर्ण

अटल व्योम v4l_prपूर्णांक_audioout(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_audioout *p = arg;

	अगर (ग_लिखो_only)
		pr_cont("index=%u\n", p->index);
	अन्यथा
		pr_cont("index=%u, name=%.*s, capability=0x%x, mode=0x%x\n",
			p->index, (पूर्णांक)माप(p->name), p->name,
			p->capability, p->mode);
पूर्ण

अटल व्योम v4l_prपूर्णांक_fmtdesc(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_fmtdesc *p = arg;

	pr_cont("index=%u, type=%s, flags=0x%x, pixelformat=%p4cc, mbus_code=0x%04x, description='%.*s'\n",
		p->index, prt_names(p->type, v4l2_type_names),
		p->flags, &p->pixelक्रमmat, p->mbus_code,
		(पूर्णांक)माप(p->description), p->description);
पूर्ण

अटल व्योम v4l_prपूर्णांक_क्रमmat(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_क्रमmat *p = arg;
	स्थिर काष्ठा v4l2_pix_क्रमmat *pix;
	स्थिर काष्ठा v4l2_pix_क्रमmat_mplane *mp;
	स्थिर काष्ठा v4l2_vbi_क्रमmat *vbi;
	स्थिर काष्ठा v4l2_sliced_vbi_क्रमmat *sliced;
	स्थिर काष्ठा v4l2_winकरोw *win;
	स्थिर काष्ठा v4l2_sdr_क्रमmat *sdr;
	स्थिर काष्ठा v4l2_meta_क्रमmat *meta;
	u32 planes;
	अचिन्हित i;

	pr_cont("type=%s", prt_names(p->type, v4l2_type_names));
	चयन (p->type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
		pix = &p->fmt.pix;
		pr_cont(", width=%u, height=%u, pixelformat=%p4cc, field=%s, bytesperline=%u, sizeimage=%u, colorspace=%d, flags=0x%x, ycbcr_enc=%u, quantization=%u, xfer_func=%u\n",
			pix->width, pix->height, &pix->pixelक्रमmat,
			prt_names(pix->field, v4l2_field_names),
			pix->bytesperline, pix->sizeimage,
			pix->colorspace, pix->flags, pix->ycbcr_enc,
			pix->quantization, pix->xfer_func);
		अवरोध;
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		mp = &p->fmt.pix_mp;
		pr_cont(", width=%u, height=%u, format=%p4cc, field=%s, colorspace=%d, num_planes=%u, flags=0x%x, ycbcr_enc=%u, quantization=%u, xfer_func=%u\n",
			mp->width, mp->height, &mp->pixelक्रमmat,
			prt_names(mp->field, v4l2_field_names),
			mp->colorspace, mp->num_planes, mp->flags,
			mp->ycbcr_enc, mp->quantization, mp->xfer_func);
		planes = min_t(u32, mp->num_planes, VIDEO_MAX_PLANES);
		क्रम (i = 0; i < planes; i++)
			prपूर्णांकk(KERN_DEBUG "plane %u: bytesperline=%u sizeimage=%u\n", i,
					mp->plane_fmt[i].bytesperline,
					mp->plane_fmt[i].sizeimage);
		अवरोध;
	हाल V4L2_BUF_TYPE_VIDEO_OVERLAY:
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY:
		win = &p->fmt.win;
		/* Note: we can't prपूर्णांक the clip list here since the clips
		 * poपूर्णांकer is a userspace poपूर्णांकer, not a kernelspace
		 * poपूर्णांकer. */
		pr_cont(", wxh=%dx%d, x,y=%d,%d, field=%s, chromakey=0x%08x, clipcount=%u, clips=%p, bitmap=%p, global_alpha=0x%02x\n",
			win->w.width, win->w.height, win->w.left, win->w.top,
			prt_names(win->field, v4l2_field_names),
			win->chromakey, win->clipcount, win->clips,
			win->biपंचांगap, win->global_alpha);
		अवरोध;
	हाल V4L2_BUF_TYPE_VBI_CAPTURE:
	हाल V4L2_BUF_TYPE_VBI_OUTPUT:
		vbi = &p->fmt.vbi;
		pr_cont(", sampling_rate=%u, offset=%u, samples_per_line=%u, sample_format=%p4cc, start=%u,%u, count=%u,%u\n",
			vbi->sampling_rate, vbi->offset,
			vbi->samples_per_line, &vbi->sample_क्रमmat,
			vbi->start[0], vbi->start[1],
			vbi->count[0], vbi->count[1]);
		अवरोध;
	हाल V4L2_BUF_TYPE_SLICED_VBI_CAPTURE:
	हाल V4L2_BUF_TYPE_SLICED_VBI_OUTPUT:
		sliced = &p->fmt.sliced;
		pr_cont(", service_set=0x%08x, io_size=%d\n",
				sliced->service_set, sliced->io_size);
		क्रम (i = 0; i < 24; i++)
			prपूर्णांकk(KERN_DEBUG "line[%02u]=0x%04x, 0x%04x\n", i,
				sliced->service_lines[0][i],
				sliced->service_lines[1][i]);
		अवरोध;
	हाल V4L2_BUF_TYPE_SDR_CAPTURE:
	हाल V4L2_BUF_TYPE_SDR_OUTPUT:
		sdr = &p->fmt.sdr;
		pr_cont(", pixelformat=%p4cc\n", &sdr->pixelक्रमmat);
		अवरोध;
	हाल V4L2_BUF_TYPE_META_CAPTURE:
	हाल V4L2_BUF_TYPE_META_OUTPUT:
		meta = &p->fmt.meta;
		pr_cont(", dataformat=%p4cc, buffersize=%u\n",
			&meta->dataक्रमmat, meta->buffersize);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम v4l_prपूर्णांक_framebuffer(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_framebuffer *p = arg;

	pr_cont("capability=0x%x, flags=0x%x, base=0x%p, width=%u, height=%u, pixelformat=%p4cc, bytesperline=%u, sizeimage=%u, colorspace=%d\n",
		p->capability, p->flags, p->base, p->fmt.width, p->fmt.height,
		&p->fmt.pixelक्रमmat, p->fmt.bytesperline, p->fmt.sizeimage,
		p->fmt.colorspace);
पूर्ण

अटल व्योम v4l_prपूर्णांक_buftype(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	pr_cont("type=%s\n", prt_names(*(u32 *)arg, v4l2_type_names));
पूर्ण

अटल व्योम v4l_prपूर्णांक_modulator(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_modulator *p = arg;

	अगर (ग_लिखो_only)
		pr_cont("index=%u, txsubchans=0x%x\n", p->index, p->txsubchans);
	अन्यथा
		pr_cont("index=%u, name=%.*s, capability=0x%x, rangelow=%u, rangehigh=%u, txsubchans=0x%x\n",
			p->index, (पूर्णांक)माप(p->name), p->name, p->capability,
			p->rangelow, p->rangehigh, p->txsubchans);
पूर्ण

अटल व्योम v4l_prपूर्णांक_tuner(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_tuner *p = arg;

	अगर (ग_लिखो_only)
		pr_cont("index=%u, audmode=%u\n", p->index, p->audmode);
	अन्यथा
		pr_cont("index=%u, name=%.*s, type=%u, capability=0x%x, rangelow=%u, rangehigh=%u, signal=%u, afc=%d, rxsubchans=0x%x, audmode=%u\n",
			p->index, (पूर्णांक)माप(p->name), p->name, p->type,
			p->capability, p->rangelow,
			p->rangehigh, p->संकेत, p->afc,
			p->rxsubchans, p->audmode);
पूर्ण

अटल व्योम v4l_prपूर्णांक_frequency(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_frequency *p = arg;

	pr_cont("tuner=%u, type=%u, frequency=%u\n",
				p->tuner, p->type, p->frequency);
पूर्ण

अटल व्योम v4l_prपूर्णांक_standard(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_standard *p = arg;

	pr_cont("index=%u, id=0x%Lx, name=%.*s, fps=%u/%u, framelines=%u\n",
		p->index,
		(अचिन्हित दीर्घ दीर्घ)p->id, (पूर्णांक)माप(p->name), p->name,
		p->frameperiod.numerator,
		p->frameperiod.denominator,
		p->framelines);
पूर्ण

अटल व्योम v4l_prपूर्णांक_std(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	pr_cont("std=0x%08Lx\n", *(स्थिर दीर्घ दीर्घ अचिन्हित *)arg);
पूर्ण

अटल व्योम v4l_prपूर्णांक_hw_freq_seek(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_hw_freq_seek *p = arg;

	pr_cont("tuner=%u, type=%u, seek_upward=%u, wrap_around=%u, spacing=%u, rangelow=%u, rangehigh=%u\n",
		p->tuner, p->type, p->seek_upward, p->wrap_around, p->spacing,
		p->rangelow, p->rangehigh);
पूर्ण

अटल व्योम v4l_prपूर्णांक_requestbuffers(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_requestbuffers *p = arg;

	pr_cont("count=%d, type=%s, memory=%s\n",
		p->count,
		prt_names(p->type, v4l2_type_names),
		prt_names(p->memory, v4l2_memory_names));
पूर्ण

अटल व्योम v4l_prपूर्णांक_buffer(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_buffer *p = arg;
	स्थिर काष्ठा v4l2_समयcode *tc = &p->समयcode;
	स्थिर काष्ठा v4l2_plane *plane;
	पूर्णांक i;

	pr_cont("%02d:%02d:%02d.%06ld index=%d, type=%s, request_fd=%d, flags=0x%08x, field=%s, sequence=%d, memory=%s",
			(पूर्णांक)p->बारtamp.tv_sec / 3600,
			((पूर्णांक)p->बारtamp.tv_sec / 60) % 60,
			((पूर्णांक)p->बारtamp.tv_sec % 60),
			(दीर्घ)p->बारtamp.tv_usec,
			p->index,
			prt_names(p->type, v4l2_type_names), p->request_fd,
			p->flags, prt_names(p->field, v4l2_field_names),
			p->sequence, prt_names(p->memory, v4l2_memory_names));

	अगर (V4L2_TYPE_IS_MULTIPLANAR(p->type) && p->m.planes) अणु
		pr_cont("\n");
		क्रम (i = 0; i < p->length; ++i) अणु
			plane = &p->m.planes[i];
			prपूर्णांकk(KERN_DEBUG
				"plane %d: bytesused=%d, data_offset=0x%08x, offset/userptr=0x%lx, length=%d\n",
				i, plane->bytesused, plane->data_offset,
				plane->m.userptr, plane->length);
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_cont(", bytesused=%d, offset/userptr=0x%lx, length=%d\n",
			p->bytesused, p->m.userptr, p->length);
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "timecode=%02d:%02d:%02d type=%d, flags=0x%08x, frames=%d, userbits=0x%08x\n",
			tc->hours, tc->minutes, tc->seconds,
			tc->type, tc->flags, tc->frames, *(__u32 *)tc->userbits);
पूर्ण

अटल व्योम v4l_prपूर्णांक_exportbuffer(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_exportbuffer *p = arg;

	pr_cont("fd=%d, type=%s, index=%u, plane=%u, flags=0x%08x\n",
		p->fd, prt_names(p->type, v4l2_type_names),
		p->index, p->plane, p->flags);
पूर्ण

अटल व्योम v4l_prपूर्णांक_create_buffers(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_create_buffers *p = arg;

	pr_cont("index=%d, count=%d, memory=%s, capabilities=0x%08x, ",
		p->index, p->count, prt_names(p->memory, v4l2_memory_names),
		p->capabilities);
	v4l_prपूर्णांक_क्रमmat(&p->क्रमmat, ग_लिखो_only);
पूर्ण

अटल व्योम v4l_prपूर्णांक_streamparm(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_streamparm *p = arg;

	pr_cont("type=%s", prt_names(p->type, v4l2_type_names));

	अगर (p->type == V4L2_BUF_TYPE_VIDEO_CAPTURE ||
	    p->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		स्थिर काष्ठा v4l2_captureparm *c = &p->parm.capture;

		pr_cont(", capability=0x%x, capturemode=0x%x, timeperframe=%d/%d, extendedmode=%d, readbuffers=%d\n",
			c->capability, c->capturemode,
			c->समयperframe.numerator, c->समयperframe.denominator,
			c->extendedmode, c->पढ़ोbuffers);
	पूर्ण अन्यथा अगर (p->type == V4L2_BUF_TYPE_VIDEO_OUTPUT ||
		   p->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		स्थिर काष्ठा v4l2_outputparm *c = &p->parm.output;

		pr_cont(", capability=0x%x, outputmode=0x%x, timeperframe=%d/%d, extendedmode=%d, writebuffers=%d\n",
			c->capability, c->outpuपंचांगode,
			c->समयperframe.numerator, c->समयperframe.denominator,
			c->extendedmode, c->ग_लिखोbuffers);
	पूर्ण अन्यथा अणु
		pr_cont("\n");
	पूर्ण
पूर्ण

अटल व्योम v4l_prपूर्णांक_queryctrl(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_queryctrl *p = arg;

	pr_cont("id=0x%x, type=%d, name=%.*s, min/max=%d/%d, step=%d, default=%d, flags=0x%08x\n",
			p->id, p->type, (पूर्णांक)माप(p->name), p->name,
			p->minimum, p->maximum,
			p->step, p->शेष_value, p->flags);
पूर्ण

अटल व्योम v4l_prपूर्णांक_query_ext_ctrl(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_query_ext_ctrl *p = arg;

	pr_cont("id=0x%x, type=%d, name=%.*s, min/max=%lld/%lld, step=%lld, default=%lld, flags=0x%08x, elem_size=%u, elems=%u, nr_of_dims=%u, dims=%u,%u,%u,%u\n",
			p->id, p->type, (पूर्णांक)माप(p->name), p->name,
			p->minimum, p->maximum,
			p->step, p->शेष_value, p->flags,
			p->elem_size, p->elems, p->nr_of_dims,
			p->dims[0], p->dims[1], p->dims[2], p->dims[3]);
पूर्ण

अटल व्योम v4l_prपूर्णांक_querymenu(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_querymenu *p = arg;

	pr_cont("id=0x%x, index=%d\n", p->id, p->index);
पूर्ण

अटल व्योम v4l_prपूर्णांक_control(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_control *p = arg;
	स्थिर अक्षर *name = v4l2_ctrl_get_name(p->id);

	अगर (name)
		pr_cont("name=%s, ", name);
	pr_cont("id=0x%x, value=%d\n", p->id, p->value);
पूर्ण

अटल व्योम v4l_prपूर्णांक_ext_controls(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_ext_controls *p = arg;
	पूर्णांक i;

	pr_cont("which=0x%x, count=%d, error_idx=%d, request_fd=%d",
			p->which, p->count, p->error_idx, p->request_fd);
	क्रम (i = 0; i < p->count; i++) अणु
		अचिन्हित पूर्णांक id = p->controls[i].id;
		स्थिर अक्षर *name = v4l2_ctrl_get_name(id);

		अगर (name)
			pr_cont(", name=%s", name);
		अगर (!p->controls[i].size)
			pr_cont(", id/val=0x%x/0x%x", id, p->controls[i].value);
		अन्यथा
			pr_cont(", id/size=0x%x/%u", id, p->controls[i].size);
	पूर्ण
	pr_cont("\n");
पूर्ण

अटल व्योम v4l_prपूर्णांक_cropcap(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_cropcap *p = arg;

	pr_cont("type=%s, bounds wxh=%dx%d, x,y=%d,%d, defrect wxh=%dx%d, x,y=%d,%d, pixelaspect %d/%d\n",
		prt_names(p->type, v4l2_type_names),
		p->bounds.width, p->bounds.height,
		p->bounds.left, p->bounds.top,
		p->defrect.width, p->defrect.height,
		p->defrect.left, p->defrect.top,
		p->pixelaspect.numerator, p->pixelaspect.denominator);
पूर्ण

अटल व्योम v4l_prपूर्णांक_crop(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_crop *p = arg;

	pr_cont("type=%s, wxh=%dx%d, x,y=%d,%d\n",
		prt_names(p->type, v4l2_type_names),
		p->c.width, p->c.height,
		p->c.left, p->c.top);
पूर्ण

अटल व्योम v4l_prपूर्णांक_selection(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_selection *p = arg;

	pr_cont("type=%s, target=%d, flags=0x%x, wxh=%dx%d, x,y=%d,%d\n",
		prt_names(p->type, v4l2_type_names),
		p->target, p->flags,
		p->r.width, p->r.height, p->r.left, p->r.top);
पूर्ण

अटल व्योम v4l_prपूर्णांक_jpegcompression(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_jpegcompression *p = arg;

	pr_cont("quality=%d, APPn=%d, APP_len=%d, COM_len=%d, jpeg_markers=0x%x\n",
		p->quality, p->APPn, p->APP_len,
		p->COM_len, p->jpeg_markers);
पूर्ण

अटल व्योम v4l_prपूर्णांक_enc_idx(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_enc_idx *p = arg;

	pr_cont("entries=%d, entries_cap=%d\n",
			p->entries, p->entries_cap);
पूर्ण

अटल व्योम v4l_prपूर्णांक_encoder_cmd(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_encoder_cmd *p = arg;

	pr_cont("cmd=%d, flags=0x%x\n",
			p->cmd, p->flags);
पूर्ण

अटल व्योम v4l_prपूर्णांक_decoder_cmd(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_decoder_cmd *p = arg;

	pr_cont("cmd=%d, flags=0x%x\n", p->cmd, p->flags);

	अगर (p->cmd == V4L2_DEC_CMD_START)
		pr_info("speed=%d, format=%u\n",
				p->start.speed, p->start.क्रमmat);
	अन्यथा अगर (p->cmd == V4L2_DEC_CMD_STOP)
		pr_info("pts=%llu\n", p->stop.pts);
पूर्ण

अटल व्योम v4l_prपूर्णांक_dbg_chip_info(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_dbg_chip_info *p = arg;

	pr_cont("type=%u, ", p->match.type);
	अगर (p->match.type == V4L2_CHIP_MATCH_I2C_DRIVER)
		pr_cont("name=%.*s, ",
				(पूर्णांक)माप(p->match.name), p->match.name);
	अन्यथा
		pr_cont("addr=%u, ", p->match.addr);
	pr_cont("name=%.*s\n", (पूर्णांक)माप(p->name), p->name);
पूर्ण

अटल व्योम v4l_prपूर्णांक_dbg_रेजिस्टर(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_dbg_रेजिस्टर *p = arg;

	pr_cont("type=%u, ", p->match.type);
	अगर (p->match.type == V4L2_CHIP_MATCH_I2C_DRIVER)
		pr_cont("name=%.*s, ",
				(पूर्णांक)माप(p->match.name), p->match.name);
	अन्यथा
		pr_cont("addr=%u, ", p->match.addr);
	pr_cont("reg=0x%llx, val=0x%llx\n",
			p->reg, p->val);
पूर्ण

अटल व्योम v4l_prपूर्णांक_dv_timings(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_dv_timings *p = arg;

	चयन (p->type) अणु
	हाल V4L2_DV_BT_656_1120:
		pr_cont("type=bt-656/1120, interlaced=%u, pixelclock=%llu, width=%u, height=%u, polarities=0x%x, hfrontporch=%u, hsync=%u, hbackporch=%u, vfrontporch=%u, vsync=%u, vbackporch=%u, il_vfrontporch=%u, il_vsync=%u, il_vbackporch=%u, standards=0x%x, flags=0x%x\n",
				p->bt.पूर्णांकerlaced, p->bt.pixelघड़ी,
				p->bt.width, p->bt.height,
				p->bt.polarities, p->bt.hfrontporch,
				p->bt.hsync, p->bt.hbackporch,
				p->bt.vfrontporch, p->bt.vsync,
				p->bt.vbackporch, p->bt.il_vfrontporch,
				p->bt.il_vsync, p->bt.il_vbackporch,
				p->bt.standards, p->bt.flags);
		अवरोध;
	शेष:
		pr_cont("type=%d\n", p->type);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम v4l_prपूर्णांक_क्रमागत_dv_timings(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_क्रमागत_dv_timings *p = arg;

	pr_cont("index=%u, ", p->index);
	v4l_prपूर्णांक_dv_timings(&p->timings, ग_लिखो_only);
पूर्ण

अटल व्योम v4l_prपूर्णांक_dv_timings_cap(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_dv_timings_cap *p = arg;

	चयन (p->type) अणु
	हाल V4L2_DV_BT_656_1120:
		pr_cont("type=bt-656/1120, width=%u-%u, height=%u-%u, pixelclock=%llu-%llu, standards=0x%x, capabilities=0x%x\n",
			p->bt.min_width, p->bt.max_width,
			p->bt.min_height, p->bt.max_height,
			p->bt.min_pixelघड़ी, p->bt.max_pixelघड़ी,
			p->bt.standards, p->bt.capabilities);
		अवरोध;
	शेष:
		pr_cont("type=%u\n", p->type);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम v4l_prपूर्णांक_frmsizeक्रमागत(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_frmsizeक्रमागत *p = arg;

	pr_cont("index=%u, pixelformat=%p4cc, type=%u",
		p->index, &p->pixel_क्रमmat, p->type);
	चयन (p->type) अणु
	हाल V4L2_FRMSIZE_TYPE_DISCRETE:
		pr_cont(", wxh=%ux%u\n",
			p->discrete.width, p->discrete.height);
		अवरोध;
	हाल V4L2_FRMSIZE_TYPE_STEPWISE:
		pr_cont(", min=%ux%u, max=%ux%u, step=%ux%u\n",
				p->stepwise.min_width,
				p->stepwise.min_height,
				p->stepwise.max_width,
				p->stepwise.max_height,
				p->stepwise.step_width,
				p->stepwise.step_height);
		अवरोध;
	हाल V4L2_FRMSIZE_TYPE_CONTINUOUS:
	शेष:
		pr_cont("\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम v4l_prपूर्णांक_frmivalक्रमागत(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_frmivalक्रमागत *p = arg;

	pr_cont("index=%u, pixelformat=%p4cc, wxh=%ux%u, type=%u",
		p->index, &p->pixel_क्रमmat, p->width, p->height, p->type);
	चयन (p->type) अणु
	हाल V4L2_FRMIVAL_TYPE_DISCRETE:
		pr_cont(", fps=%d/%d\n",
				p->discrete.numerator,
				p->discrete.denominator);
		अवरोध;
	हाल V4L2_FRMIVAL_TYPE_STEPWISE:
		pr_cont(", min=%d/%d, max=%d/%d, step=%d/%d\n",
				p->stepwise.min.numerator,
				p->stepwise.min.denominator,
				p->stepwise.max.numerator,
				p->stepwise.max.denominator,
				p->stepwise.step.numerator,
				p->stepwise.step.denominator);
		अवरोध;
	हाल V4L2_FRMIVAL_TYPE_CONTINUOUS:
	शेष:
		pr_cont("\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम v4l_prपूर्णांक_event(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_event *p = arg;
	स्थिर काष्ठा v4l2_event_ctrl *c;

	pr_cont("type=0x%x, pending=%u, sequence=%u, id=%u, timestamp=%llu.%9.9llu\n",
			p->type, p->pending, p->sequence, p->id,
			p->बारtamp.tv_sec, p->बारtamp.tv_nsec);
	चयन (p->type) अणु
	हाल V4L2_EVENT_VSYNC:
		prपूर्णांकk(KERN_DEBUG "field=%s\n",
			prt_names(p->u.vsync.field, v4l2_field_names));
		अवरोध;
	हाल V4L2_EVENT_CTRL:
		c = &p->u.ctrl;
		prपूर्णांकk(KERN_DEBUG "changes=0x%x, type=%u, ",
			c->changes, c->type);
		अगर (c->type == V4L2_CTRL_TYPE_INTEGER64)
			pr_cont("value64=%lld, ", c->value64);
		अन्यथा
			pr_cont("value=%d, ", c->value);
		pr_cont("flags=0x%x, minimum=%d, maximum=%d, step=%d, default_value=%d\n",
			c->flags, c->minimum, c->maximum,
			c->step, c->शेष_value);
		अवरोध;
	हाल V4L2_EVENT_FRAME_SYNC:
		pr_cont("frame_sequence=%u\n",
			p->u.frame_sync.frame_sequence);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम v4l_prपूर्णांक_event_subscription(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_event_subscription *p = arg;

	pr_cont("type=0x%x, id=0x%x, flags=0x%x\n",
			p->type, p->id, p->flags);
पूर्ण

अटल व्योम v4l_prपूर्णांक_sliced_vbi_cap(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_sliced_vbi_cap *p = arg;
	पूर्णांक i;

	pr_cont("type=%s, service_set=0x%08x\n",
			prt_names(p->type, v4l2_type_names), p->service_set);
	क्रम (i = 0; i < 24; i++)
		prपूर्णांकk(KERN_DEBUG "line[%02u]=0x%04x, 0x%04x\n", i,
				p->service_lines[0][i],
				p->service_lines[1][i]);
पूर्ण

अटल व्योम v4l_prपूर्णांक_freq_band(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_frequency_band *p = arg;

	pr_cont("tuner=%u, type=%u, index=%u, capability=0x%x, rangelow=%u, rangehigh=%u, modulation=0x%x\n",
			p->tuner, p->type, p->index,
			p->capability, p->rangelow,
			p->rangehigh, p->modulation);
पूर्ण

अटल व्योम v4l_prपूर्णांक_edid(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	स्थिर काष्ठा v4l2_edid *p = arg;

	pr_cont("pad=%u, start_block=%u, blocks=%u\n",
		p->pad, p->start_block, p->blocks);
पूर्ण

अटल व्योम v4l_prपूर्णांक_u32(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	pr_cont("value=%u\n", *(स्थिर u32 *)arg);
पूर्ण

अटल व्योम v4l_prपूर्णांक_newline(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	pr_cont("\n");
पूर्ण

अटल व्योम v4l_prपूर्णांक_शेष(स्थिर व्योम *arg, bool ग_लिखो_only)
अणु
	pr_cont("driver-specific ioctl\n");
पूर्ण

अटल पूर्णांक check_ext_ctrls(काष्ठा v4l2_ext_controls *c, पूर्णांक allow_priv)
अणु
	__u32 i;

	/* zero the reserved fields */
	c->reserved[0] = 0;
	क्रम (i = 0; i < c->count; i++)
		c->controls[i].reserved2[0] = 0;

	/* V4L2_CID_PRIVATE_BASE cannot be used as control class
	   when using extended controls.
	   Only when passed in through VIDIOC_G_CTRL and VIDIOC_S_CTRL
	   is it allowed क्रम backwards compatibility.
	 */
	अगर (!allow_priv && c->which == V4L2_CID_PRIVATE_BASE)
		वापस 0;
	अगर (!c->which)
		वापस 1;
	/* Check that all controls are from the same control class. */
	क्रम (i = 0; i < c->count; i++) अणु
		अगर (V4L2_CTRL_ID2WHICH(c->controls[i].id) != c->which) अणु
			c->error_idx = i;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक check_fmt(काष्ठा file *file, क्रमागत v4l2_buf_type type)
अणु
	स्थिर u32 vid_caps = V4L2_CAP_VIDEO_CAPTURE |
			     V4L2_CAP_VIDEO_CAPTURE_MPLANE |
			     V4L2_CAP_VIDEO_OUTPUT |
			     V4L2_CAP_VIDEO_OUTPUT_MPLANE |
			     V4L2_CAP_VIDEO_M2M | V4L2_CAP_VIDEO_M2M_MPLANE;
	स्थिर u32 meta_caps = V4L2_CAP_META_CAPTURE |
			      V4L2_CAP_META_OUTPUT;
	काष्ठा video_device *vfd = video_devdata(file);
	स्थिर काष्ठा v4l2_ioctl_ops *ops = vfd->ioctl_ops;
	bool is_vid = vfd->vfl_type == VFL_TYPE_VIDEO &&
		      (vfd->device_caps & vid_caps);
	bool is_vbi = vfd->vfl_type == VFL_TYPE_VBI;
	bool is_sdr = vfd->vfl_type == VFL_TYPE_SDR;
	bool is_tch = vfd->vfl_type == VFL_TYPE_TOUCH;
	bool is_meta = vfd->vfl_type == VFL_TYPE_VIDEO &&
		       (vfd->device_caps & meta_caps);
	bool is_rx = vfd->vfl_dir != VFL_सूची_TX;
	bool is_tx = vfd->vfl_dir != VFL_सूची_RX;

	अगर (ops == शून्य)
		वापस -EINVAL;

	चयन (type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
		अगर ((is_vid || is_tch) && is_rx &&
		    (ops->vidioc_g_fmt_vid_cap || ops->vidioc_g_fmt_vid_cap_mplane))
			वापस 0;
		अवरोध;
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
		अगर ((is_vid || is_tch) && is_rx && ops->vidioc_g_fmt_vid_cap_mplane)
			वापस 0;
		अवरोध;
	हाल V4L2_BUF_TYPE_VIDEO_OVERLAY:
		अगर (is_vid && is_rx && ops->vidioc_g_fmt_vid_overlay)
			वापस 0;
		अवरोध;
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
		अगर (is_vid && is_tx &&
		    (ops->vidioc_g_fmt_vid_out || ops->vidioc_g_fmt_vid_out_mplane))
			वापस 0;
		अवरोध;
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		अगर (is_vid && is_tx && ops->vidioc_g_fmt_vid_out_mplane)
			वापस 0;
		अवरोध;
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY:
		अगर (is_vid && is_tx && ops->vidioc_g_fmt_vid_out_overlay)
			वापस 0;
		अवरोध;
	हाल V4L2_BUF_TYPE_VBI_CAPTURE:
		अगर (is_vbi && is_rx && ops->vidioc_g_fmt_vbi_cap)
			वापस 0;
		अवरोध;
	हाल V4L2_BUF_TYPE_VBI_OUTPUT:
		अगर (is_vbi && is_tx && ops->vidioc_g_fmt_vbi_out)
			वापस 0;
		अवरोध;
	हाल V4L2_BUF_TYPE_SLICED_VBI_CAPTURE:
		अगर (is_vbi && is_rx && ops->vidioc_g_fmt_sliced_vbi_cap)
			वापस 0;
		अवरोध;
	हाल V4L2_BUF_TYPE_SLICED_VBI_OUTPUT:
		अगर (is_vbi && is_tx && ops->vidioc_g_fmt_sliced_vbi_out)
			वापस 0;
		अवरोध;
	हाल V4L2_BUF_TYPE_SDR_CAPTURE:
		अगर (is_sdr && is_rx && ops->vidioc_g_fmt_sdr_cap)
			वापस 0;
		अवरोध;
	हाल V4L2_BUF_TYPE_SDR_OUTPUT:
		अगर (is_sdr && is_tx && ops->vidioc_g_fmt_sdr_out)
			वापस 0;
		अवरोध;
	हाल V4L2_BUF_TYPE_META_CAPTURE:
		अगर (is_meta && is_rx && ops->vidioc_g_fmt_meta_cap)
			वापस 0;
		अवरोध;
	हाल V4L2_BUF_TYPE_META_OUTPUT:
		अगर (is_meta && is_tx && ops->vidioc_g_fmt_meta_out)
			वापस 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल व्योम v4l_sanitize_क्रमmat(काष्ठा v4l2_क्रमmat *fmt)
अणु
	अचिन्हित पूर्णांक offset;

	/* Make sure num_planes is not bogus */
	अगर (fmt->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ||
	    fmt->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		fmt->fmt.pix_mp.num_planes = min_t(u32, fmt->fmt.pix_mp.num_planes,
					       VIDEO_MAX_PLANES);

	/*
	 * The v4l2_pix_क्रमmat काष्ठाure has been extended with fields that were
	 * not previously required to be set to zero by applications. The priv
	 * field, when set to a magic value, indicates the the extended fields
	 * are valid. Otherwise they will contain undefined values. To simplअगरy
	 * the API towards drivers zero the extended fields and set the priv
	 * field to the magic value when the extended pixel क्रमmat काष्ठाure
	 * isn't used by applications.
	 */

	अगर (fmt->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    fmt->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		वापस;

	अगर (fmt->fmt.pix.priv == V4L2_PIX_FMT_PRIV_MAGIC)
		वापस;

	fmt->fmt.pix.priv = V4L2_PIX_FMT_PRIV_MAGIC;

	offset = दुरत्व(काष्ठा v4l2_pix_क्रमmat, priv)
	       + माप(fmt->fmt.pix.priv);
	स_रखो(((व्योम *)&fmt->fmt.pix) + offset, 0,
	       माप(fmt->fmt.pix) - offset);
पूर्ण

अटल पूर्णांक v4l_querycap(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा v4l2_capability *cap = (काष्ठा v4l2_capability *)arg;
	काष्ठा video_device *vfd = video_devdata(file);
	पूर्णांक ret;

	cap->version = LINUX_VERSION_CODE;
	cap->device_caps = vfd->device_caps;
	cap->capabilities = vfd->device_caps | V4L2_CAP_DEVICE_CAPS;

	ret = ops->vidioc_querycap(file, fh, cap);

	/*
	 * Drivers must not change device_caps, so check क्रम this and
	 * warn अगर this happened.
	 */
	WARN_ON(cap->device_caps != vfd->device_caps);
	/*
	 * Check that capabilities is a superset of
	 * vfd->device_caps | V4L2_CAP_DEVICE_CAPS
	 */
	WARN_ON((cap->capabilities &
		 (vfd->device_caps | V4L2_CAP_DEVICE_CAPS)) !=
		(vfd->device_caps | V4L2_CAP_DEVICE_CAPS));
	cap->capabilities |= V4L2_CAP_EXT_PIX_FORMAT;
	cap->device_caps |= V4L2_CAP_EXT_PIX_FORMAT;

	वापस ret;
पूर्ण

अटल पूर्णांक v4l_g_input(स्थिर काष्ठा v4l2_ioctl_ops *ops,
		       काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd = video_devdata(file);

	अगर (vfd->device_caps & V4L2_CAP_IO_MC) अणु
		*(पूर्णांक *)arg = 0;
		वापस 0;
	पूर्ण

	वापस ops->vidioc_g_input(file, fh, arg);
पूर्ण

अटल पूर्णांक v4l_g_output(स्थिर काष्ठा v4l2_ioctl_ops *ops,
			काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd = video_devdata(file);

	अगर (vfd->device_caps & V4L2_CAP_IO_MC) अणु
		*(पूर्णांक *)arg = 0;
		वापस 0;
	पूर्ण

	वापस ops->vidioc_g_output(file, fh, arg);
पूर्ण

अटल पूर्णांक v4l_s_input(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	पूर्णांक ret;

	ret = v4l_enable_media_source(vfd);
	अगर (ret)
		वापस ret;

	अगर (vfd->device_caps & V4L2_CAP_IO_MC)
		वापस  *(पूर्णांक *)arg ? -EINVAL : 0;

	वापस ops->vidioc_s_input(file, fh, *(अचिन्हित पूर्णांक *)arg);
पूर्ण

अटल पूर्णांक v4l_s_output(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd = video_devdata(file);

	अगर (vfd->device_caps & V4L2_CAP_IO_MC)
		वापस  *(पूर्णांक *)arg ? -EINVAL : 0;

	वापस ops->vidioc_s_output(file, fh, *(अचिन्हित पूर्णांक *)arg);
पूर्ण

अटल पूर्णांक v4l_g_priority(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd;
	u32 *p = arg;

	vfd = video_devdata(file);
	*p = v4l2_prio_max(vfd->prio);
	वापस 0;
पूर्ण

अटल पूर्णांक v4l_s_priority(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd;
	काष्ठा v4l2_fh *vfh;
	u32 *p = arg;

	vfd = video_devdata(file);
	अगर (!test_bit(V4L2_FL_USES_V4L2_FH, &vfd->flags))
		वापस -ENOTTY;
	vfh = file->निजी_data;
	वापस v4l2_prio_change(vfd->prio, &vfh->prio, *p);
पूर्ण

अटल पूर्णांक v4l_क्रमागतinput(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा v4l2_input *p = arg;

	/*
	 * We set the flags क्रम CAP_DV_TIMINGS &
	 * CAP_STD here based on ioctl handler provided by the
	 * driver. If the driver करोesn't support these
	 * क्रम a specअगरic input, it must override these flags.
	 */
	अगर (is_valid_ioctl(vfd, VIDIOC_S_STD))
		p->capabilities |= V4L2_IN_CAP_STD;

	अगर (vfd->device_caps & V4L2_CAP_IO_MC) अणु
		अगर (p->index)
			वापस -EINVAL;
		strscpy(p->name, vfd->name, माप(p->name));
		p->type = V4L2_INPUT_TYPE_CAMERA;
		वापस 0;
	पूर्ण

	वापस ops->vidioc_क्रमागत_input(file, fh, p);
पूर्ण

अटल पूर्णांक v4l_क्रमागतoutput(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा v4l2_output *p = arg;

	/*
	 * We set the flags क्रम CAP_DV_TIMINGS &
	 * CAP_STD here based on ioctl handler provided by the
	 * driver. If the driver करोesn't support these
	 * क्रम a specअगरic output, it must override these flags.
	 */
	अगर (is_valid_ioctl(vfd, VIDIOC_S_STD))
		p->capabilities |= V4L2_OUT_CAP_STD;

	अगर (vfd->device_caps & V4L2_CAP_IO_MC) अणु
		अगर (p->index)
			वापस -EINVAL;
		strscpy(p->name, vfd->name, माप(p->name));
		p->type = V4L2_OUTPUT_TYPE_ANALOG;
		वापस 0;
	पूर्ण

	वापस ops->vidioc_क्रमागत_output(file, fh, p);
पूर्ण

अटल व्योम v4l_fill_fmtdesc(काष्ठा v4l2_fmtdesc *fmt)
अणु
	स्थिर अचिन्हित sz = माप(fmt->description);
	स्थिर अक्षर *descr = शून्य;
	u32 flags = 0;

	/*
	 * We depart from the normal coding style here since the descriptions
	 * should be aligned so it is easy to see which descriptions will be
	 * दीर्घer than 31 अक्षरacters (the max length क्रम a description).
	 * And frankly, this is easier to पढ़ो anyway.
	 *
	 * Note that gcc will use O(log N) comparisons to find the right हाल.
	 */
	चयन (fmt->pixelक्रमmat) अणु
	/* Max description length mask:	descr = "0123456789012345678901234567890" */
	हाल V4L2_PIX_FMT_RGB332:	descr = "8-bit RGB 3-3-2"; अवरोध;
	हाल V4L2_PIX_FMT_RGB444:	descr = "16-bit A/XRGB 4-4-4-4"; अवरोध;
	हाल V4L2_PIX_FMT_ARGB444:	descr = "16-bit ARGB 4-4-4-4"; अवरोध;
	हाल V4L2_PIX_FMT_XRGB444:	descr = "16-bit XRGB 4-4-4-4"; अवरोध;
	हाल V4L2_PIX_FMT_RGBA444:	descr = "16-bit RGBA 4-4-4-4"; अवरोध;
	हाल V4L2_PIX_FMT_RGBX444:	descr = "16-bit RGBX 4-4-4-4"; अवरोध;
	हाल V4L2_PIX_FMT_ABGR444:	descr = "16-bit ABGR 4-4-4-4"; अवरोध;
	हाल V4L2_PIX_FMT_XBGR444:	descr = "16-bit XBGR 4-4-4-4"; अवरोध;
	हाल V4L2_PIX_FMT_BGRA444:	descr = "16-bit BGRA 4-4-4-4"; अवरोध;
	हाल V4L2_PIX_FMT_BGRX444:	descr = "16-bit BGRX 4-4-4-4"; अवरोध;
	हाल V4L2_PIX_FMT_RGB555:	descr = "16-bit A/XRGB 1-5-5-5"; अवरोध;
	हाल V4L2_PIX_FMT_ARGB555:	descr = "16-bit ARGB 1-5-5-5"; अवरोध;
	हाल V4L2_PIX_FMT_XRGB555:	descr = "16-bit XRGB 1-5-5-5"; अवरोध;
	हाल V4L2_PIX_FMT_ABGR555:	descr = "16-bit ABGR 1-5-5-5"; अवरोध;
	हाल V4L2_PIX_FMT_XBGR555:	descr = "16-bit XBGR 1-5-5-5"; अवरोध;
	हाल V4L2_PIX_FMT_RGBA555:	descr = "16-bit RGBA 5-5-5-1"; अवरोध;
	हाल V4L2_PIX_FMT_RGBX555:	descr = "16-bit RGBX 5-5-5-1"; अवरोध;
	हाल V4L2_PIX_FMT_BGRA555:	descr = "16-bit BGRA 5-5-5-1"; अवरोध;
	हाल V4L2_PIX_FMT_BGRX555:	descr = "16-bit BGRX 5-5-5-1"; अवरोध;
	हाल V4L2_PIX_FMT_RGB565:	descr = "16-bit RGB 5-6-5"; अवरोध;
	हाल V4L2_PIX_FMT_RGB555X:	descr = "16-bit A/XRGB 1-5-5-5 BE"; अवरोध;
	हाल V4L2_PIX_FMT_ARGB555X:	descr = "16-bit ARGB 1-5-5-5 BE"; अवरोध;
	हाल V4L2_PIX_FMT_XRGB555X:	descr = "16-bit XRGB 1-5-5-5 BE"; अवरोध;
	हाल V4L2_PIX_FMT_RGB565X:	descr = "16-bit RGB 5-6-5 BE"; अवरोध;
	हाल V4L2_PIX_FMT_BGR666:	descr = "18-bit BGRX 6-6-6-14"; अवरोध;
	हाल V4L2_PIX_FMT_BGR24:	descr = "24-bit BGR 8-8-8"; अवरोध;
	हाल V4L2_PIX_FMT_RGB24:	descr = "24-bit RGB 8-8-8"; अवरोध;
	हाल V4L2_PIX_FMT_BGR32:	descr = "32-bit BGRA/X 8-8-8-8"; अवरोध;
	हाल V4L2_PIX_FMT_ABGR32:	descr = "32-bit BGRA 8-8-8-8"; अवरोध;
	हाल V4L2_PIX_FMT_XBGR32:	descr = "32-bit BGRX 8-8-8-8"; अवरोध;
	हाल V4L2_PIX_FMT_RGB32:	descr = "32-bit A/XRGB 8-8-8-8"; अवरोध;
	हाल V4L2_PIX_FMT_ARGB32:	descr = "32-bit ARGB 8-8-8-8"; अवरोध;
	हाल V4L2_PIX_FMT_XRGB32:	descr = "32-bit XRGB 8-8-8-8"; अवरोध;
	हाल V4L2_PIX_FMT_BGRA32:	descr = "32-bit ABGR 8-8-8-8"; अवरोध;
	हाल V4L2_PIX_FMT_BGRX32:	descr = "32-bit XBGR 8-8-8-8"; अवरोध;
	हाल V4L2_PIX_FMT_RGBA32:	descr = "32-bit RGBA 8-8-8-8"; अवरोध;
	हाल V4L2_PIX_FMT_RGBX32:	descr = "32-bit RGBX 8-8-8-8"; अवरोध;
	हाल V4L2_PIX_FMT_GREY:		descr = "8-bit Greyscale"; अवरोध;
	हाल V4L2_PIX_FMT_Y4:		descr = "4-bit Greyscale"; अवरोध;
	हाल V4L2_PIX_FMT_Y6:		descr = "6-bit Greyscale"; अवरोध;
	हाल V4L2_PIX_FMT_Y10:		descr = "10-bit Greyscale"; अवरोध;
	हाल V4L2_PIX_FMT_Y12:		descr = "12-bit Greyscale"; अवरोध;
	हाल V4L2_PIX_FMT_Y14:		descr = "14-bit Greyscale"; अवरोध;
	हाल V4L2_PIX_FMT_Y16:		descr = "16-bit Greyscale"; अवरोध;
	हाल V4L2_PIX_FMT_Y16_BE:	descr = "16-bit Greyscale BE"; अवरोध;
	हाल V4L2_PIX_FMT_Y10BPACK:	descr = "10-bit Greyscale (Packed)"; अवरोध;
	हाल V4L2_PIX_FMT_Y10P:		descr = "10-bit Greyscale (MIPI Packed)"; अवरोध;
	हाल V4L2_PIX_FMT_Y8I:		descr = "Interleaved 8-bit Greyscale"; अवरोध;
	हाल V4L2_PIX_FMT_Y12I:		descr = "Interleaved 12-bit Greyscale"; अवरोध;
	हाल V4L2_PIX_FMT_Z16:		descr = "16-bit Depth"; अवरोध;
	हाल V4L2_PIX_FMT_INZI:		descr = "Planar 10:16 Greyscale Depth"; अवरोध;
	हाल V4L2_PIX_FMT_CNF4:		descr = "4-bit Depth Confidence (Packed)"; अवरोध;
	हाल V4L2_PIX_FMT_PAL8:		descr = "8-bit Palette"; अवरोध;
	हाल V4L2_PIX_FMT_UV8:		descr = "8-bit Chrominance UV 4-4"; अवरोध;
	हाल V4L2_PIX_FMT_YVU410:	descr = "Planar YVU 4:1:0"; अवरोध;
	हाल V4L2_PIX_FMT_YVU420:	descr = "Planar YVU 4:2:0"; अवरोध;
	हाल V4L2_PIX_FMT_YUYV:		descr = "YUYV 4:2:2"; अवरोध;
	हाल V4L2_PIX_FMT_YYUV:		descr = "YYUV 4:2:2"; अवरोध;
	हाल V4L2_PIX_FMT_YVYU:		descr = "YVYU 4:2:2"; अवरोध;
	हाल V4L2_PIX_FMT_UYVY:		descr = "UYVY 4:2:2"; अवरोध;
	हाल V4L2_PIX_FMT_VYUY:		descr = "VYUY 4:2:2"; अवरोध;
	हाल V4L2_PIX_FMT_YUV422P:	descr = "Planar YUV 4:2:2"; अवरोध;
	हाल V4L2_PIX_FMT_YUV411P:	descr = "Planar YUV 4:1:1"; अवरोध;
	हाल V4L2_PIX_FMT_Y41P:		descr = "YUV 4:1:1 (Packed)"; अवरोध;
	हाल V4L2_PIX_FMT_YUV444:	descr = "16-bit A/XYUV 4-4-4-4"; अवरोध;
	हाल V4L2_PIX_FMT_YUV555:	descr = "16-bit A/XYUV 1-5-5-5"; अवरोध;
	हाल V4L2_PIX_FMT_YUV565:	descr = "16-bit YUV 5-6-5"; अवरोध;
	हाल V4L2_PIX_FMT_YUV24:	descr = "24-bit YUV 4:4:4 8-8-8"; अवरोध;
	हाल V4L2_PIX_FMT_YUV32:	descr = "32-bit A/XYUV 8-8-8-8"; अवरोध;
	हाल V4L2_PIX_FMT_AYUV32:	descr = "32-bit AYUV 8-8-8-8"; अवरोध;
	हाल V4L2_PIX_FMT_XYUV32:	descr = "32-bit XYUV 8-8-8-8"; अवरोध;
	हाल V4L2_PIX_FMT_VUYA32:	descr = "32-bit VUYA 8-8-8-8"; अवरोध;
	हाल V4L2_PIX_FMT_VUYX32:	descr = "32-bit VUYX 8-8-8-8"; अवरोध;
	हाल V4L2_PIX_FMT_YUV410:	descr = "Planar YUV 4:1:0"; अवरोध;
	हाल V4L2_PIX_FMT_YUV420:	descr = "Planar YUV 4:2:0"; अवरोध;
	हाल V4L2_PIX_FMT_HI240:	descr = "8-bit Dithered RGB (BTTV)"; अवरोध;
	हाल V4L2_PIX_FMT_HM12:		descr = "YUV 4:2:0 (16x16 Macroblocks)"; अवरोध;
	हाल V4L2_PIX_FMT_M420:		descr = "YUV 4:2:0 (M420)"; अवरोध;
	हाल V4L2_PIX_FMT_NV12:		descr = "Y/CbCr 4:2:0"; अवरोध;
	हाल V4L2_PIX_FMT_NV21:		descr = "Y/CrCb 4:2:0"; अवरोध;
	हाल V4L2_PIX_FMT_NV16:		descr = "Y/CbCr 4:2:2"; अवरोध;
	हाल V4L2_PIX_FMT_NV61:		descr = "Y/CrCb 4:2:2"; अवरोध;
	हाल V4L2_PIX_FMT_NV24:		descr = "Y/CbCr 4:4:4"; अवरोध;
	हाल V4L2_PIX_FMT_NV42:		descr = "Y/CrCb 4:4:4"; अवरोध;
	हाल V4L2_PIX_FMT_NV12M:	descr = "Y/CbCr 4:2:0 (N-C)"; अवरोध;
	हाल V4L2_PIX_FMT_NV21M:	descr = "Y/CrCb 4:2:0 (N-C)"; अवरोध;
	हाल V4L2_PIX_FMT_NV16M:	descr = "Y/CbCr 4:2:2 (N-C)"; अवरोध;
	हाल V4L2_PIX_FMT_NV61M:	descr = "Y/CrCb 4:2:2 (N-C)"; अवरोध;
	हाल V4L2_PIX_FMT_NV12MT:	descr = "Y/CbCr 4:2:0 (64x32 MB, N-C)"; अवरोध;
	हाल V4L2_PIX_FMT_NV12MT_16X16:	descr = "Y/CbCr 4:2:0 (16x16 MB, N-C)"; अवरोध;
	हाल V4L2_PIX_FMT_YUV420M:	descr = "Planar YUV 4:2:0 (N-C)"; अवरोध;
	हाल V4L2_PIX_FMT_YVU420M:	descr = "Planar YVU 4:2:0 (N-C)"; अवरोध;
	हाल V4L2_PIX_FMT_YUV422M:	descr = "Planar YUV 4:2:2 (N-C)"; अवरोध;
	हाल V4L2_PIX_FMT_YVU422M:	descr = "Planar YVU 4:2:2 (N-C)"; अवरोध;
	हाल V4L2_PIX_FMT_YUV444M:	descr = "Planar YUV 4:4:4 (N-C)"; अवरोध;
	हाल V4L2_PIX_FMT_YVU444M:	descr = "Planar YVU 4:4:4 (N-C)"; अवरोध;
	हाल V4L2_PIX_FMT_SBGGR8:	descr = "8-bit Bayer BGBG/GRGR"; अवरोध;
	हाल V4L2_PIX_FMT_SGBRG8:	descr = "8-bit Bayer GBGB/RGRG"; अवरोध;
	हाल V4L2_PIX_FMT_SGRBG8:	descr = "8-bit Bayer GRGR/BGBG"; अवरोध;
	हाल V4L2_PIX_FMT_SRGGB8:	descr = "8-bit Bayer RGRG/GBGB"; अवरोध;
	हाल V4L2_PIX_FMT_SBGGR10:	descr = "10-bit Bayer BGBG/GRGR"; अवरोध;
	हाल V4L2_PIX_FMT_SGBRG10:	descr = "10-bit Bayer GBGB/RGRG"; अवरोध;
	हाल V4L2_PIX_FMT_SGRBG10:	descr = "10-bit Bayer GRGR/BGBG"; अवरोध;
	हाल V4L2_PIX_FMT_SRGGB10:	descr = "10-bit Bayer RGRG/GBGB"; अवरोध;
	हाल V4L2_PIX_FMT_SBGGR10P:	descr = "10-bit Bayer BGBG/GRGR Packed"; अवरोध;
	हाल V4L2_PIX_FMT_SGBRG10P:	descr = "10-bit Bayer GBGB/RGRG Packed"; अवरोध;
	हाल V4L2_PIX_FMT_SGRBG10P:	descr = "10-bit Bayer GRGR/BGBG Packed"; अवरोध;
	हाल V4L2_PIX_FMT_SRGGB10P:	descr = "10-bit Bayer RGRG/GBGB Packed"; अवरोध;
	हाल V4L2_PIX_FMT_IPU3_SBGGR10: descr = "10-bit bayer BGGR IPU3 Packed"; अवरोध;
	हाल V4L2_PIX_FMT_IPU3_SGBRG10: descr = "10-bit bayer GBRG IPU3 Packed"; अवरोध;
	हाल V4L2_PIX_FMT_IPU3_SGRBG10: descr = "10-bit bayer GRBG IPU3 Packed"; अवरोध;
	हाल V4L2_PIX_FMT_IPU3_SRGGB10: descr = "10-bit bayer RGGB IPU3 Packed"; अवरोध;
	हाल V4L2_PIX_FMT_SBGGR10ALAW8:	descr = "8-bit Bayer BGBG/GRGR (A-law)"; अवरोध;
	हाल V4L2_PIX_FMT_SGBRG10ALAW8:	descr = "8-bit Bayer GBGB/RGRG (A-law)"; अवरोध;
	हाल V4L2_PIX_FMT_SGRBG10ALAW8:	descr = "8-bit Bayer GRGR/BGBG (A-law)"; अवरोध;
	हाल V4L2_PIX_FMT_SRGGB10ALAW8:	descr = "8-bit Bayer RGRG/GBGB (A-law)"; अवरोध;
	हाल V4L2_PIX_FMT_SBGGR10DPCM8:	descr = "8-bit Bayer BGBG/GRGR (DPCM)"; अवरोध;
	हाल V4L2_PIX_FMT_SGBRG10DPCM8:	descr = "8-bit Bayer GBGB/RGRG (DPCM)"; अवरोध;
	हाल V4L2_PIX_FMT_SGRBG10DPCM8:	descr = "8-bit Bayer GRGR/BGBG (DPCM)"; अवरोध;
	हाल V4L2_PIX_FMT_SRGGB10DPCM8:	descr = "8-bit Bayer RGRG/GBGB (DPCM)"; अवरोध;
	हाल V4L2_PIX_FMT_SBGGR12:	descr = "12-bit Bayer BGBG/GRGR"; अवरोध;
	हाल V4L2_PIX_FMT_SGBRG12:	descr = "12-bit Bayer GBGB/RGRG"; अवरोध;
	हाल V4L2_PIX_FMT_SGRBG12:	descr = "12-bit Bayer GRGR/BGBG"; अवरोध;
	हाल V4L2_PIX_FMT_SRGGB12:	descr = "12-bit Bayer RGRG/GBGB"; अवरोध;
	हाल V4L2_PIX_FMT_SBGGR12P:	descr = "12-bit Bayer BGBG/GRGR Packed"; अवरोध;
	हाल V4L2_PIX_FMT_SGBRG12P:	descr = "12-bit Bayer GBGB/RGRG Packed"; अवरोध;
	हाल V4L2_PIX_FMT_SGRBG12P:	descr = "12-bit Bayer GRGR/BGBG Packed"; अवरोध;
	हाल V4L2_PIX_FMT_SRGGB12P:	descr = "12-bit Bayer RGRG/GBGB Packed"; अवरोध;
	हाल V4L2_PIX_FMT_SBGGR14:	descr = "14-bit Bayer BGBG/GRGR"; अवरोध;
	हाल V4L2_PIX_FMT_SGBRG14:	descr = "14-bit Bayer GBGB/RGRG"; अवरोध;
	हाल V4L2_PIX_FMT_SGRBG14:	descr = "14-bit Bayer GRGR/BGBG"; अवरोध;
	हाल V4L2_PIX_FMT_SRGGB14:	descr = "14-bit Bayer RGRG/GBGB"; अवरोध;
	हाल V4L2_PIX_FMT_SBGGR14P:	descr = "14-bit Bayer BGBG/GRGR Packed"; अवरोध;
	हाल V4L2_PIX_FMT_SGBRG14P:	descr = "14-bit Bayer GBGB/RGRG Packed"; अवरोध;
	हाल V4L2_PIX_FMT_SGRBG14P:	descr = "14-bit Bayer GRGR/BGBG Packed"; अवरोध;
	हाल V4L2_PIX_FMT_SRGGB14P:	descr = "14-bit Bayer RGRG/GBGB Packed"; अवरोध;
	हाल V4L2_PIX_FMT_SBGGR16:	descr = "16-bit Bayer BGBG/GRGR"; अवरोध;
	हाल V4L2_PIX_FMT_SGBRG16:	descr = "16-bit Bayer GBGB/RGRG"; अवरोध;
	हाल V4L2_PIX_FMT_SGRBG16:	descr = "16-bit Bayer GRGR/BGBG"; अवरोध;
	हाल V4L2_PIX_FMT_SRGGB16:	descr = "16-bit Bayer RGRG/GBGB"; अवरोध;
	हाल V4L2_PIX_FMT_SN9C20X_I420:	descr = "GSPCA SN9C20X I420"; अवरोध;
	हाल V4L2_PIX_FMT_SPCA501:	descr = "GSPCA SPCA501"; अवरोध;
	हाल V4L2_PIX_FMT_SPCA505:	descr = "GSPCA SPCA505"; अवरोध;
	हाल V4L2_PIX_FMT_SPCA508:	descr = "GSPCA SPCA508"; अवरोध;
	हाल V4L2_PIX_FMT_STV0680:	descr = "GSPCA STV0680"; अवरोध;
	हाल V4L2_PIX_FMT_TM6000:	descr = "A/V + VBI Mux Packet"; अवरोध;
	हाल V4L2_PIX_FMT_CIT_YYVYUY:	descr = "GSPCA CIT YYVYUY"; अवरोध;
	हाल V4L2_PIX_FMT_KONICA420:	descr = "GSPCA KONICA420"; अवरोध;
	हाल V4L2_PIX_FMT_HSV24:	descr = "24-bit HSV 8-8-8"; अवरोध;
	हाल V4L2_PIX_FMT_HSV32:	descr = "32-bit XHSV 8-8-8-8"; अवरोध;
	हाल V4L2_SDR_FMT_CU8:		descr = "Complex U8"; अवरोध;
	हाल V4L2_SDR_FMT_CU16LE:	descr = "Complex U16LE"; अवरोध;
	हाल V4L2_SDR_FMT_CS8:		descr = "Complex S8"; अवरोध;
	हाल V4L2_SDR_FMT_CS14LE:	descr = "Complex S14LE"; अवरोध;
	हाल V4L2_SDR_FMT_RU12LE:	descr = "Real U12LE"; अवरोध;
	हाल V4L2_SDR_FMT_PCU16BE:	descr = "Planar Complex U16BE"; अवरोध;
	हाल V4L2_SDR_FMT_PCU18BE:	descr = "Planar Complex U18BE"; अवरोध;
	हाल V4L2_SDR_FMT_PCU20BE:	descr = "Planar Complex U20BE"; अवरोध;
	हाल V4L2_TCH_FMT_DELTA_TD16:	descr = "16-bit Signed Deltas"; अवरोध;
	हाल V4L2_TCH_FMT_DELTA_TD08:	descr = "8-bit Signed Deltas"; अवरोध;
	हाल V4L2_TCH_FMT_TU16:		descr = "16-bit Unsigned Touch Data"; अवरोध;
	हाल V4L2_TCH_FMT_TU08:		descr = "8-bit Unsigned Touch Data"; अवरोध;
	हाल V4L2_META_FMT_VSP1_HGO:	descr = "R-Car VSP1 1-D Histogram"; अवरोध;
	हाल V4L2_META_FMT_VSP1_HGT:	descr = "R-Car VSP1 2-D Histogram"; अवरोध;
	हाल V4L2_META_FMT_UVC:		descr = "UVC Payload Header Metadata"; अवरोध;
	हाल V4L2_META_FMT_D4XX:	descr = "Intel D4xx UVC Metadata"; अवरोध;
	हाल V4L2_META_FMT_VIVID:       descr = "Vivid Metadata"; अवरोध;
	हाल V4L2_META_FMT_RK_ISP1_PARAMS:	descr = "Rockchip ISP1 3A Parameters"; अवरोध;
	हाल V4L2_META_FMT_RK_ISP1_STAT_3A:	descr = "Rockchip ISP1 3A Statistics"; अवरोध;

	शेष:
		/* Compressed क्रमmats */
		flags = V4L2_FMT_FLAG_COMPRESSED;
		चयन (fmt->pixelक्रमmat) अणु
		/* Max description length mask:	descr = "0123456789012345678901234567890" */
		हाल V4L2_PIX_FMT_MJPEG:	descr = "Motion-JPEG"; अवरोध;
		हाल V4L2_PIX_FMT_JPEG:		descr = "JFIF JPEG"; अवरोध;
		हाल V4L2_PIX_FMT_DV:		descr = "1394"; अवरोध;
		हाल V4L2_PIX_FMT_MPEG:		descr = "MPEG-1/2/4"; अवरोध;
		हाल V4L2_PIX_FMT_H264:		descr = "H.264"; अवरोध;
		हाल V4L2_PIX_FMT_H264_NO_SC:	descr = "H.264 (No Start Codes)"; अवरोध;
		हाल V4L2_PIX_FMT_H264_MVC:	descr = "H.264 MVC"; अवरोध;
		हाल V4L2_PIX_FMT_H264_SLICE:	descr = "H.264 Parsed Slice Data"; अवरोध;
		हाल V4L2_PIX_FMT_H263:		descr = "H.263"; अवरोध;
		हाल V4L2_PIX_FMT_MPEG1:	descr = "MPEG-1 ES"; अवरोध;
		हाल V4L2_PIX_FMT_MPEG2:	descr = "MPEG-2 ES"; अवरोध;
		हाल V4L2_PIX_FMT_MPEG2_SLICE:	descr = "MPEG-2 Parsed Slice Data"; अवरोध;
		हाल V4L2_PIX_FMT_MPEG4:	descr = "MPEG-4 Part 2 ES"; अवरोध;
		हाल V4L2_PIX_FMT_XVID:		descr = "Xvid"; अवरोध;
		हाल V4L2_PIX_FMT_VC1_ANNEX_G:	descr = "VC-1 (SMPTE 412M Annex G)"; अवरोध;
		हाल V4L2_PIX_FMT_VC1_ANNEX_L:	descr = "VC-1 (SMPTE 412M Annex L)"; अवरोध;
		हाल V4L2_PIX_FMT_VP8:		descr = "VP8"; अवरोध;
		हाल V4L2_PIX_FMT_VP8_FRAME:    descr = "VP8 Frame"; अवरोध;
		हाल V4L2_PIX_FMT_VP9:		descr = "VP9"; अवरोध;
		हाल V4L2_PIX_FMT_HEVC:		descr = "HEVC"; अवरोध; /* aka H.265 */
		हाल V4L2_PIX_FMT_HEVC_SLICE:	descr = "HEVC Parsed Slice Data"; अवरोध;
		हाल V4L2_PIX_FMT_FWHT:		descr = "FWHT"; अवरोध; /* used in vicodec */
		हाल V4L2_PIX_FMT_FWHT_STATELESS:	descr = "FWHT Stateless"; अवरोध; /* used in vicodec */
		हाल V4L2_PIX_FMT_CPIA1:	descr = "GSPCA CPiA YUV"; अवरोध;
		हाल V4L2_PIX_FMT_WNVA:		descr = "WNVA"; अवरोध;
		हाल V4L2_PIX_FMT_SN9C10X:	descr = "GSPCA SN9C10X"; अवरोध;
		हाल V4L2_PIX_FMT_PWC1:		descr = "Raw Philips Webcam Type (Old)"; अवरोध;
		हाल V4L2_PIX_FMT_PWC2:		descr = "Raw Philips Webcam Type (New)"; अवरोध;
		हाल V4L2_PIX_FMT_ET61X251:	descr = "GSPCA ET61X251"; अवरोध;
		हाल V4L2_PIX_FMT_SPCA561:	descr = "GSPCA SPCA561"; अवरोध;
		हाल V4L2_PIX_FMT_PAC207:	descr = "GSPCA PAC207"; अवरोध;
		हाल V4L2_PIX_FMT_MR97310A:	descr = "GSPCA MR97310A"; अवरोध;
		हाल V4L2_PIX_FMT_JL2005BCD:	descr = "GSPCA JL2005BCD"; अवरोध;
		हाल V4L2_PIX_FMT_SN9C2028:	descr = "GSPCA SN9C2028"; अवरोध;
		हाल V4L2_PIX_FMT_SQ905C:	descr = "GSPCA SQ905C"; अवरोध;
		हाल V4L2_PIX_FMT_PJPG:		descr = "GSPCA PJPG"; अवरोध;
		हाल V4L2_PIX_FMT_OV511:	descr = "GSPCA OV511"; अवरोध;
		हाल V4L2_PIX_FMT_OV518:	descr = "GSPCA OV518"; अवरोध;
		हाल V4L2_PIX_FMT_JPGL:		descr = "JPEG Lite"; अवरोध;
		हाल V4L2_PIX_FMT_SE401:	descr = "GSPCA SE401"; अवरोध;
		हाल V4L2_PIX_FMT_S5C_UYVY_JPG:	descr = "S5C73MX interleaved UYVY/JPEG"; अवरोध;
		हाल V4L2_PIX_FMT_MT21C:	descr = "Mediatek Compressed Format"; अवरोध;
		हाल V4L2_PIX_FMT_SUNXI_TILED_NV12: descr = "Sunxi Tiled NV12 Format"; अवरोध;
		शेष:
			अगर (fmt->description[0])
				वापस;
			WARN(1, "Unknown pixelformat 0x%08x\n", fmt->pixelक्रमmat);
			flags = 0;
			snम_लिखो(fmt->description, sz, "%p4cc",
				 &fmt->pixelक्रमmat);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (descr)
		WARN_ON(strscpy(fmt->description, descr, sz) < 0);
	fmt->flags |= flags;
पूर्ण

अटल पूर्णांक v4l_क्रमागत_fmt(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा v4l2_fmtdesc *p = arg;
	पूर्णांक ret = check_fmt(file, p->type);
	u32 mbus_code;
	u32 cap_mask;

	अगर (ret)
		वापस ret;
	ret = -EINVAL;

	अगर (!(vdev->device_caps & V4L2_CAP_IO_MC))
		p->mbus_code = 0;

	mbus_code = p->mbus_code;
	CLEAR_AFTER_FIELD(p, type);
	p->mbus_code = mbus_code;

	चयन (p->type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
		cap_mask = V4L2_CAP_VIDEO_CAPTURE_MPLANE |
			   V4L2_CAP_VIDEO_M2M_MPLANE;
		अगर (!!(vdev->device_caps & cap_mask) !=
		    (p->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE))
			अवरोध;

		अगर (unlikely(!ops->vidioc_क्रमागत_fmt_vid_cap))
			अवरोध;
		ret = ops->vidioc_क्रमागत_fmt_vid_cap(file, fh, arg);
		अवरोध;
	हाल V4L2_BUF_TYPE_VIDEO_OVERLAY:
		अगर (unlikely(!ops->vidioc_क्रमागत_fmt_vid_overlay))
			अवरोध;
		ret = ops->vidioc_क्रमागत_fmt_vid_overlay(file, fh, arg);
		अवरोध;
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		cap_mask = V4L2_CAP_VIDEO_OUTPUT_MPLANE |
			   V4L2_CAP_VIDEO_M2M_MPLANE;
		अगर (!!(vdev->device_caps & cap_mask) !=
		    (p->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE))
			अवरोध;

		अगर (unlikely(!ops->vidioc_क्रमागत_fmt_vid_out))
			अवरोध;
		ret = ops->vidioc_क्रमागत_fmt_vid_out(file, fh, arg);
		अवरोध;
	हाल V4L2_BUF_TYPE_SDR_CAPTURE:
		अगर (unlikely(!ops->vidioc_क्रमागत_fmt_sdr_cap))
			अवरोध;
		ret = ops->vidioc_क्रमागत_fmt_sdr_cap(file, fh, arg);
		अवरोध;
	हाल V4L2_BUF_TYPE_SDR_OUTPUT:
		अगर (unlikely(!ops->vidioc_क्रमागत_fmt_sdr_out))
			अवरोध;
		ret = ops->vidioc_क्रमागत_fmt_sdr_out(file, fh, arg);
		अवरोध;
	हाल V4L2_BUF_TYPE_META_CAPTURE:
		अगर (unlikely(!ops->vidioc_क्रमागत_fmt_meta_cap))
			अवरोध;
		ret = ops->vidioc_क्रमागत_fmt_meta_cap(file, fh, arg);
		अवरोध;
	हाल V4L2_BUF_TYPE_META_OUTPUT:
		अगर (unlikely(!ops->vidioc_क्रमागत_fmt_meta_out))
			अवरोध;
		ret = ops->vidioc_क्रमागत_fmt_meta_out(file, fh, arg);
		अवरोध;
	पूर्ण
	अगर (ret == 0)
		v4l_fill_fmtdesc(p);
	वापस ret;
पूर्ण

अटल व्योम v4l_pix_क्रमmat_touch(काष्ठा v4l2_pix_क्रमmat *p)
अणु
	/*
	 * The v4l2_pix_क्रमmat काष्ठाure contains fields that make no sense क्रम
	 * touch. Set them to शेष values in this हाल.
	 */

	p->field = V4L2_FIELD_NONE;
	p->colorspace = V4L2_COLORSPACE_RAW;
	p->flags = 0;
	p->ycbcr_enc = 0;
	p->quantization = 0;
	p->xfer_func = 0;
पूर्ण

अटल पूर्णांक v4l_g_fmt(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा v4l2_क्रमmat *p = arg;
	काष्ठा video_device *vfd = video_devdata(file);
	पूर्णांक ret = check_fmt(file, p->type);

	अगर (ret)
		वापस ret;

	/*
	 * fmt can't be cleared for these overlay types due to the 'clips'
	 * 'clipcount' and 'bitmap' poपूर्णांकers in काष्ठा v4l2_winकरोw.
	 * Those are provided by the user. So handle these two overlay types
	 * first, and then just करो a simple स_रखो क्रम the other types.
	 */
	चयन (p->type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_OVERLAY:
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY: अणु
		काष्ठा v4l2_clip *clips = p->fmt.win.clips;
		u32 clipcount = p->fmt.win.clipcount;
		व्योम __user *biपंचांगap = p->fmt.win.biपंचांगap;

		स_रखो(&p->fmt, 0, माप(p->fmt));
		p->fmt.win.clips = clips;
		p->fmt.win.clipcount = clipcount;
		p->fmt.win.biपंचांगap = biपंचांगap;
		अवरोध;
	पूर्ण
	शेष:
		स_रखो(&p->fmt, 0, माप(p->fmt));
		अवरोध;
	पूर्ण

	चयन (p->type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
		अगर (unlikely(!ops->vidioc_g_fmt_vid_cap))
			अवरोध;
		p->fmt.pix.priv = V4L2_PIX_FMT_PRIV_MAGIC;
		ret = ops->vidioc_g_fmt_vid_cap(file, fh, arg);
		/* just in हाल the driver zeroed it again */
		p->fmt.pix.priv = V4L2_PIX_FMT_PRIV_MAGIC;
		अगर (vfd->vfl_type == VFL_TYPE_TOUCH)
			v4l_pix_क्रमmat_touch(&p->fmt.pix);
		वापस ret;
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
		वापस ops->vidioc_g_fmt_vid_cap_mplane(file, fh, arg);
	हाल V4L2_BUF_TYPE_VIDEO_OVERLAY:
		वापस ops->vidioc_g_fmt_vid_overlay(file, fh, arg);
	हाल V4L2_BUF_TYPE_VBI_CAPTURE:
		वापस ops->vidioc_g_fmt_vbi_cap(file, fh, arg);
	हाल V4L2_BUF_TYPE_SLICED_VBI_CAPTURE:
		वापस ops->vidioc_g_fmt_sliced_vbi_cap(file, fh, arg);
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
		अगर (unlikely(!ops->vidioc_g_fmt_vid_out))
			अवरोध;
		p->fmt.pix.priv = V4L2_PIX_FMT_PRIV_MAGIC;
		ret = ops->vidioc_g_fmt_vid_out(file, fh, arg);
		/* just in हाल the driver zeroed it again */
		p->fmt.pix.priv = V4L2_PIX_FMT_PRIV_MAGIC;
		वापस ret;
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		वापस ops->vidioc_g_fmt_vid_out_mplane(file, fh, arg);
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY:
		वापस ops->vidioc_g_fmt_vid_out_overlay(file, fh, arg);
	हाल V4L2_BUF_TYPE_VBI_OUTPUT:
		वापस ops->vidioc_g_fmt_vbi_out(file, fh, arg);
	हाल V4L2_BUF_TYPE_SLICED_VBI_OUTPUT:
		वापस ops->vidioc_g_fmt_sliced_vbi_out(file, fh, arg);
	हाल V4L2_BUF_TYPE_SDR_CAPTURE:
		वापस ops->vidioc_g_fmt_sdr_cap(file, fh, arg);
	हाल V4L2_BUF_TYPE_SDR_OUTPUT:
		वापस ops->vidioc_g_fmt_sdr_out(file, fh, arg);
	हाल V4L2_BUF_TYPE_META_CAPTURE:
		वापस ops->vidioc_g_fmt_meta_cap(file, fh, arg);
	हाल V4L2_BUF_TYPE_META_OUTPUT:
		वापस ops->vidioc_g_fmt_meta_out(file, fh, arg);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक v4l_s_fmt(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा v4l2_क्रमmat *p = arg;
	काष्ठा video_device *vfd = video_devdata(file);
	पूर्णांक ret = check_fmt(file, p->type);
	अचिन्हित पूर्णांक i;

	अगर (ret)
		वापस ret;

	ret = v4l_enable_media_source(vfd);
	अगर (ret)
		वापस ret;
	v4l_sanitize_क्रमmat(p);

	चयन (p->type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
		अगर (unlikely(!ops->vidioc_s_fmt_vid_cap))
			अवरोध;
		CLEAR_AFTER_FIELD(p, fmt.pix);
		ret = ops->vidioc_s_fmt_vid_cap(file, fh, arg);
		/* just in हाल the driver zeroed it again */
		p->fmt.pix.priv = V4L2_PIX_FMT_PRIV_MAGIC;
		अगर (vfd->vfl_type == VFL_TYPE_TOUCH)
			v4l_pix_क्रमmat_touch(&p->fmt.pix);
		वापस ret;
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
		अगर (unlikely(!ops->vidioc_s_fmt_vid_cap_mplane))
			अवरोध;
		CLEAR_AFTER_FIELD(p, fmt.pix_mp.xfer_func);
		क्रम (i = 0; i < p->fmt.pix_mp.num_planes; i++)
			CLEAR_AFTER_FIELD(&p->fmt.pix_mp.plane_fmt[i],
					  bytesperline);
		वापस ops->vidioc_s_fmt_vid_cap_mplane(file, fh, arg);
	हाल V4L2_BUF_TYPE_VIDEO_OVERLAY:
		अगर (unlikely(!ops->vidioc_s_fmt_vid_overlay))
			अवरोध;
		CLEAR_AFTER_FIELD(p, fmt.win);
		वापस ops->vidioc_s_fmt_vid_overlay(file, fh, arg);
	हाल V4L2_BUF_TYPE_VBI_CAPTURE:
		अगर (unlikely(!ops->vidioc_s_fmt_vbi_cap))
			अवरोध;
		CLEAR_AFTER_FIELD(p, fmt.vbi.flags);
		वापस ops->vidioc_s_fmt_vbi_cap(file, fh, arg);
	हाल V4L2_BUF_TYPE_SLICED_VBI_CAPTURE:
		अगर (unlikely(!ops->vidioc_s_fmt_sliced_vbi_cap))
			अवरोध;
		CLEAR_AFTER_FIELD(p, fmt.sliced.io_size);
		वापस ops->vidioc_s_fmt_sliced_vbi_cap(file, fh, arg);
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
		अगर (unlikely(!ops->vidioc_s_fmt_vid_out))
			अवरोध;
		CLEAR_AFTER_FIELD(p, fmt.pix);
		ret = ops->vidioc_s_fmt_vid_out(file, fh, arg);
		/* just in हाल the driver zeroed it again */
		p->fmt.pix.priv = V4L2_PIX_FMT_PRIV_MAGIC;
		वापस ret;
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		अगर (unlikely(!ops->vidioc_s_fmt_vid_out_mplane))
			अवरोध;
		CLEAR_AFTER_FIELD(p, fmt.pix_mp.xfer_func);
		क्रम (i = 0; i < p->fmt.pix_mp.num_planes; i++)
			CLEAR_AFTER_FIELD(&p->fmt.pix_mp.plane_fmt[i],
					  bytesperline);
		वापस ops->vidioc_s_fmt_vid_out_mplane(file, fh, arg);
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY:
		अगर (unlikely(!ops->vidioc_s_fmt_vid_out_overlay))
			अवरोध;
		CLEAR_AFTER_FIELD(p, fmt.win);
		वापस ops->vidioc_s_fmt_vid_out_overlay(file, fh, arg);
	हाल V4L2_BUF_TYPE_VBI_OUTPUT:
		अगर (unlikely(!ops->vidioc_s_fmt_vbi_out))
			अवरोध;
		CLEAR_AFTER_FIELD(p, fmt.vbi.flags);
		वापस ops->vidioc_s_fmt_vbi_out(file, fh, arg);
	हाल V4L2_BUF_TYPE_SLICED_VBI_OUTPUT:
		अगर (unlikely(!ops->vidioc_s_fmt_sliced_vbi_out))
			अवरोध;
		CLEAR_AFTER_FIELD(p, fmt.sliced.io_size);
		वापस ops->vidioc_s_fmt_sliced_vbi_out(file, fh, arg);
	हाल V4L2_BUF_TYPE_SDR_CAPTURE:
		अगर (unlikely(!ops->vidioc_s_fmt_sdr_cap))
			अवरोध;
		CLEAR_AFTER_FIELD(p, fmt.sdr.buffersize);
		वापस ops->vidioc_s_fmt_sdr_cap(file, fh, arg);
	हाल V4L2_BUF_TYPE_SDR_OUTPUT:
		अगर (unlikely(!ops->vidioc_s_fmt_sdr_out))
			अवरोध;
		CLEAR_AFTER_FIELD(p, fmt.sdr.buffersize);
		वापस ops->vidioc_s_fmt_sdr_out(file, fh, arg);
	हाल V4L2_BUF_TYPE_META_CAPTURE:
		अगर (unlikely(!ops->vidioc_s_fmt_meta_cap))
			अवरोध;
		CLEAR_AFTER_FIELD(p, fmt.meta);
		वापस ops->vidioc_s_fmt_meta_cap(file, fh, arg);
	हाल V4L2_BUF_TYPE_META_OUTPUT:
		अगर (unlikely(!ops->vidioc_s_fmt_meta_out))
			अवरोध;
		CLEAR_AFTER_FIELD(p, fmt.meta);
		वापस ops->vidioc_s_fmt_meta_out(file, fh, arg);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक v4l_try_fmt(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा v4l2_क्रमmat *p = arg;
	काष्ठा video_device *vfd = video_devdata(file);
	पूर्णांक ret = check_fmt(file, p->type);
	अचिन्हित पूर्णांक i;

	अगर (ret)
		वापस ret;

	v4l_sanitize_क्रमmat(p);

	चयन (p->type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
		अगर (unlikely(!ops->vidioc_try_fmt_vid_cap))
			अवरोध;
		CLEAR_AFTER_FIELD(p, fmt.pix);
		ret = ops->vidioc_try_fmt_vid_cap(file, fh, arg);
		/* just in हाल the driver zeroed it again */
		p->fmt.pix.priv = V4L2_PIX_FMT_PRIV_MAGIC;
		अगर (vfd->vfl_type == VFL_TYPE_TOUCH)
			v4l_pix_क्रमmat_touch(&p->fmt.pix);
		वापस ret;
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
		अगर (unlikely(!ops->vidioc_try_fmt_vid_cap_mplane))
			अवरोध;
		CLEAR_AFTER_FIELD(p, fmt.pix_mp.xfer_func);
		क्रम (i = 0; i < p->fmt.pix_mp.num_planes; i++)
			CLEAR_AFTER_FIELD(&p->fmt.pix_mp.plane_fmt[i],
					  bytesperline);
		वापस ops->vidioc_try_fmt_vid_cap_mplane(file, fh, arg);
	हाल V4L2_BUF_TYPE_VIDEO_OVERLAY:
		अगर (unlikely(!ops->vidioc_try_fmt_vid_overlay))
			अवरोध;
		CLEAR_AFTER_FIELD(p, fmt.win);
		वापस ops->vidioc_try_fmt_vid_overlay(file, fh, arg);
	हाल V4L2_BUF_TYPE_VBI_CAPTURE:
		अगर (unlikely(!ops->vidioc_try_fmt_vbi_cap))
			अवरोध;
		CLEAR_AFTER_FIELD(p, fmt.vbi.flags);
		वापस ops->vidioc_try_fmt_vbi_cap(file, fh, arg);
	हाल V4L2_BUF_TYPE_SLICED_VBI_CAPTURE:
		अगर (unlikely(!ops->vidioc_try_fmt_sliced_vbi_cap))
			अवरोध;
		CLEAR_AFTER_FIELD(p, fmt.sliced.io_size);
		वापस ops->vidioc_try_fmt_sliced_vbi_cap(file, fh, arg);
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
		अगर (unlikely(!ops->vidioc_try_fmt_vid_out))
			अवरोध;
		CLEAR_AFTER_FIELD(p, fmt.pix);
		ret = ops->vidioc_try_fmt_vid_out(file, fh, arg);
		/* just in हाल the driver zeroed it again */
		p->fmt.pix.priv = V4L2_PIX_FMT_PRIV_MAGIC;
		वापस ret;
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		अगर (unlikely(!ops->vidioc_try_fmt_vid_out_mplane))
			अवरोध;
		CLEAR_AFTER_FIELD(p, fmt.pix_mp.xfer_func);
		क्रम (i = 0; i < p->fmt.pix_mp.num_planes; i++)
			CLEAR_AFTER_FIELD(&p->fmt.pix_mp.plane_fmt[i],
					  bytesperline);
		वापस ops->vidioc_try_fmt_vid_out_mplane(file, fh, arg);
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY:
		अगर (unlikely(!ops->vidioc_try_fmt_vid_out_overlay))
			अवरोध;
		CLEAR_AFTER_FIELD(p, fmt.win);
		वापस ops->vidioc_try_fmt_vid_out_overlay(file, fh, arg);
	हाल V4L2_BUF_TYPE_VBI_OUTPUT:
		अगर (unlikely(!ops->vidioc_try_fmt_vbi_out))
			अवरोध;
		CLEAR_AFTER_FIELD(p, fmt.vbi.flags);
		वापस ops->vidioc_try_fmt_vbi_out(file, fh, arg);
	हाल V4L2_BUF_TYPE_SLICED_VBI_OUTPUT:
		अगर (unlikely(!ops->vidioc_try_fmt_sliced_vbi_out))
			अवरोध;
		CLEAR_AFTER_FIELD(p, fmt.sliced.io_size);
		वापस ops->vidioc_try_fmt_sliced_vbi_out(file, fh, arg);
	हाल V4L2_BUF_TYPE_SDR_CAPTURE:
		अगर (unlikely(!ops->vidioc_try_fmt_sdr_cap))
			अवरोध;
		CLEAR_AFTER_FIELD(p, fmt.sdr.buffersize);
		वापस ops->vidioc_try_fmt_sdr_cap(file, fh, arg);
	हाल V4L2_BUF_TYPE_SDR_OUTPUT:
		अगर (unlikely(!ops->vidioc_try_fmt_sdr_out))
			अवरोध;
		CLEAR_AFTER_FIELD(p, fmt.sdr.buffersize);
		वापस ops->vidioc_try_fmt_sdr_out(file, fh, arg);
	हाल V4L2_BUF_TYPE_META_CAPTURE:
		अगर (unlikely(!ops->vidioc_try_fmt_meta_cap))
			अवरोध;
		CLEAR_AFTER_FIELD(p, fmt.meta);
		वापस ops->vidioc_try_fmt_meta_cap(file, fh, arg);
	हाल V4L2_BUF_TYPE_META_OUTPUT:
		अगर (unlikely(!ops->vidioc_try_fmt_meta_out))
			अवरोध;
		CLEAR_AFTER_FIELD(p, fmt.meta);
		वापस ops->vidioc_try_fmt_meta_out(file, fh, arg);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक v4l_streamon(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	वापस ops->vidioc_streamon(file, fh, *(अचिन्हित पूर्णांक *)arg);
पूर्ण

अटल पूर्णांक v4l_streamoff(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	वापस ops->vidioc_streamoff(file, fh, *(अचिन्हित पूर्णांक *)arg);
पूर्ण

अटल पूर्णांक v4l_g_tuner(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा v4l2_tuner *p = arg;
	पूर्णांक err;

	p->type = (vfd->vfl_type == VFL_TYPE_RADIO) ?
			V4L2_TUNER_RADIO : V4L2_TUNER_ANALOG_TV;
	err = ops->vidioc_g_tuner(file, fh, p);
	अगर (!err)
		p->capability |= V4L2_TUNER_CAP_FREQ_BANDS;
	वापस err;
पूर्ण

अटल पूर्णांक v4l_s_tuner(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा v4l2_tuner *p = arg;
	पूर्णांक ret;

	ret = v4l_enable_media_source(vfd);
	अगर (ret)
		वापस ret;
	p->type = (vfd->vfl_type == VFL_TYPE_RADIO) ?
			V4L2_TUNER_RADIO : V4L2_TUNER_ANALOG_TV;
	वापस ops->vidioc_s_tuner(file, fh, p);
पूर्ण

अटल पूर्णांक v4l_g_modulator(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा v4l2_modulator *p = arg;
	पूर्णांक err;

	अगर (vfd->vfl_type == VFL_TYPE_RADIO)
		p->type = V4L2_TUNER_RADIO;

	err = ops->vidioc_g_modulator(file, fh, p);
	अगर (!err)
		p->capability |= V4L2_TUNER_CAP_FREQ_BANDS;
	वापस err;
पूर्ण

अटल पूर्णांक v4l_s_modulator(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा v4l2_modulator *p = arg;

	अगर (vfd->vfl_type == VFL_TYPE_RADIO)
		p->type = V4L2_TUNER_RADIO;

	वापस ops->vidioc_s_modulator(file, fh, p);
पूर्ण

अटल पूर्णांक v4l_g_frequency(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा v4l2_frequency *p = arg;

	अगर (vfd->vfl_type == VFL_TYPE_SDR)
		p->type = V4L2_TUNER_SDR;
	अन्यथा
		p->type = (vfd->vfl_type == VFL_TYPE_RADIO) ?
				V4L2_TUNER_RADIO : V4L2_TUNER_ANALOG_TV;
	वापस ops->vidioc_g_frequency(file, fh, p);
पूर्ण

अटल पूर्णांक v4l_s_frequency(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	स्थिर काष्ठा v4l2_frequency *p = arg;
	क्रमागत v4l2_tuner_type type;
	पूर्णांक ret;

	ret = v4l_enable_media_source(vfd);
	अगर (ret)
		वापस ret;
	अगर (vfd->vfl_type == VFL_TYPE_SDR) अणु
		अगर (p->type != V4L2_TUNER_SDR && p->type != V4L2_TUNER_RF)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		type = (vfd->vfl_type == VFL_TYPE_RADIO) ?
				V4L2_TUNER_RADIO : V4L2_TUNER_ANALOG_TV;
		अगर (type != p->type)
			वापस -EINVAL;
	पूर्ण
	वापस ops->vidioc_s_frequency(file, fh, p);
पूर्ण

अटल पूर्णांक v4l_क्रमागतstd(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा v4l2_standard *p = arg;

	वापस v4l_video_std_क्रमागतstd(p, vfd->tvnorms);
पूर्ण

अटल पूर्णांक v4l_s_std(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	v4l2_std_id id = *(v4l2_std_id *)arg, norm;
	पूर्णांक ret;

	ret = v4l_enable_media_source(vfd);
	अगर (ret)
		वापस ret;
	norm = id & vfd->tvnorms;
	अगर (vfd->tvnorms && !norm)	/* Check अगर std is supported */
		वापस -EINVAL;

	/* Calls the specअगरic handler */
	वापस ops->vidioc_s_std(file, fh, norm);
पूर्ण

अटल पूर्णांक v4l_querystd(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	v4l2_std_id *p = arg;
	पूर्णांक ret;

	ret = v4l_enable_media_source(vfd);
	अगर (ret)
		वापस ret;
	/*
	 * If no संकेत is detected, then the driver should वापस
	 * V4L2_STD_UNKNOWN. Otherwise it should वापस tvnorms with
	 * any standards that करो not apply हटाओd.
	 *
	 * This means that tuners, audio and video decoders can join
	 * their efक्रमts to improve the standards detection.
	 */
	*p = vfd->tvnorms;
	वापस ops->vidioc_querystd(file, fh, arg);
पूर्ण

अटल पूर्णांक v4l_s_hw_freq_seek(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा v4l2_hw_freq_seek *p = arg;
	क्रमागत v4l2_tuner_type type;
	पूर्णांक ret;

	ret = v4l_enable_media_source(vfd);
	अगर (ret)
		वापस ret;
	/* s_hw_freq_seek is not supported क्रम SDR क्रम now */
	अगर (vfd->vfl_type == VFL_TYPE_SDR)
		वापस -EINVAL;

	type = (vfd->vfl_type == VFL_TYPE_RADIO) ?
		V4L2_TUNER_RADIO : V4L2_TUNER_ANALOG_TV;
	अगर (p->type != type)
		वापस -EINVAL;
	वापस ops->vidioc_s_hw_freq_seek(file, fh, p);
पूर्ण

अटल पूर्णांक v4l_overlay(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	वापस ops->vidioc_overlay(file, fh, *(अचिन्हित पूर्णांक *)arg);
पूर्ण

अटल पूर्णांक v4l_reqbufs(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा v4l2_requestbuffers *p = arg;
	पूर्णांक ret = check_fmt(file, p->type);

	अगर (ret)
		वापस ret;

	CLEAR_AFTER_FIELD(p, capabilities);

	वापस ops->vidioc_reqbufs(file, fh, p);
पूर्ण

अटल पूर्णांक v4l_querybuf(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा v4l2_buffer *p = arg;
	पूर्णांक ret = check_fmt(file, p->type);

	वापस ret ? ret : ops->vidioc_querybuf(file, fh, p);
पूर्ण

अटल पूर्णांक v4l_qbuf(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा v4l2_buffer *p = arg;
	पूर्णांक ret = check_fmt(file, p->type);

	वापस ret ? ret : ops->vidioc_qbuf(file, fh, p);
पूर्ण

अटल पूर्णांक v4l_dqbuf(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा v4l2_buffer *p = arg;
	पूर्णांक ret = check_fmt(file, p->type);

	वापस ret ? ret : ops->vidioc_dqbuf(file, fh, p);
पूर्ण

अटल पूर्णांक v4l_create_bufs(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा v4l2_create_buffers *create = arg;
	पूर्णांक ret = check_fmt(file, create->क्रमmat.type);

	अगर (ret)
		वापस ret;

	CLEAR_AFTER_FIELD(create, capabilities);

	v4l_sanitize_क्रमmat(&create->क्रमmat);

	ret = ops->vidioc_create_bufs(file, fh, create);

	अगर (create->क्रमmat.type == V4L2_BUF_TYPE_VIDEO_CAPTURE ||
	    create->क्रमmat.type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
		create->क्रमmat.fmt.pix.priv = V4L2_PIX_FMT_PRIV_MAGIC;

	वापस ret;
पूर्ण

अटल पूर्णांक v4l_prepare_buf(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा v4l2_buffer *b = arg;
	पूर्णांक ret = check_fmt(file, b->type);

	वापस ret ? ret : ops->vidioc_prepare_buf(file, fh, b);
पूर्ण

अटल पूर्णांक v4l_g_parm(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा v4l2_streamparm *p = arg;
	v4l2_std_id std;
	पूर्णांक ret = check_fmt(file, p->type);

	अगर (ret)
		वापस ret;
	अगर (ops->vidioc_g_parm)
		वापस ops->vidioc_g_parm(file, fh, p);
	अगर (p->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    p->type != V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		वापस -EINVAL;
	p->parm.capture.पढ़ोbuffers = 2;
	ret = ops->vidioc_g_std(file, fh, &std);
	अगर (ret == 0)
		v4l2_video_std_frame_period(std, &p->parm.capture.समयperframe);
	वापस ret;
पूर्ण

अटल पूर्णांक v4l_s_parm(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा v4l2_streamparm *p = arg;
	पूर्णांक ret = check_fmt(file, p->type);

	अगर (ret)
		वापस ret;

	/* Note: extendedmode is never used in drivers */
	अगर (V4L2_TYPE_IS_OUTPUT(p->type)) अणु
		स_रखो(p->parm.output.reserved, 0,
		       माप(p->parm.output.reserved));
		p->parm.output.extendedmode = 0;
		p->parm.output.outpuपंचांगode &= V4L2_MODE_HIGHQUALITY;
	पूर्ण अन्यथा अणु
		स_रखो(p->parm.capture.reserved, 0,
		       माप(p->parm.capture.reserved));
		p->parm.capture.extendedmode = 0;
		p->parm.capture.capturemode &= V4L2_MODE_HIGHQUALITY;
	पूर्ण
	वापस ops->vidioc_s_parm(file, fh, p);
पूर्ण

अटल पूर्णांक v4l_queryctrl(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा v4l2_queryctrl *p = arg;
	काष्ठा v4l2_fh *vfh =
		test_bit(V4L2_FL_USES_V4L2_FH, &vfd->flags) ? fh : शून्य;

	अगर (vfh && vfh->ctrl_handler)
		वापस v4l2_queryctrl(vfh->ctrl_handler, p);
	अगर (vfd->ctrl_handler)
		वापस v4l2_queryctrl(vfd->ctrl_handler, p);
	अगर (ops->vidioc_queryctrl)
		वापस ops->vidioc_queryctrl(file, fh, p);
	वापस -ENOTTY;
पूर्ण

अटल पूर्णांक v4l_query_ext_ctrl(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा v4l2_query_ext_ctrl *p = arg;
	काष्ठा v4l2_fh *vfh =
		test_bit(V4L2_FL_USES_V4L2_FH, &vfd->flags) ? fh : शून्य;

	अगर (vfh && vfh->ctrl_handler)
		वापस v4l2_query_ext_ctrl(vfh->ctrl_handler, p);
	अगर (vfd->ctrl_handler)
		वापस v4l2_query_ext_ctrl(vfd->ctrl_handler, p);
	अगर (ops->vidioc_query_ext_ctrl)
		वापस ops->vidioc_query_ext_ctrl(file, fh, p);
	वापस -ENOTTY;
पूर्ण

अटल पूर्णांक v4l_querymenu(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा v4l2_querymenu *p = arg;
	काष्ठा v4l2_fh *vfh =
		test_bit(V4L2_FL_USES_V4L2_FH, &vfd->flags) ? fh : शून्य;

	अगर (vfh && vfh->ctrl_handler)
		वापस v4l2_querymenu(vfh->ctrl_handler, p);
	अगर (vfd->ctrl_handler)
		वापस v4l2_querymenu(vfd->ctrl_handler, p);
	अगर (ops->vidioc_querymenu)
		वापस ops->vidioc_querymenu(file, fh, p);
	वापस -ENOTTY;
पूर्ण

अटल पूर्णांक v4l_g_ctrl(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा v4l2_control *p = arg;
	काष्ठा v4l2_fh *vfh =
		test_bit(V4L2_FL_USES_V4L2_FH, &vfd->flags) ? fh : शून्य;
	काष्ठा v4l2_ext_controls ctrls;
	काष्ठा v4l2_ext_control ctrl;

	अगर (vfh && vfh->ctrl_handler)
		वापस v4l2_g_ctrl(vfh->ctrl_handler, p);
	अगर (vfd->ctrl_handler)
		वापस v4l2_g_ctrl(vfd->ctrl_handler, p);
	अगर (ops->vidioc_g_ctrl)
		वापस ops->vidioc_g_ctrl(file, fh, p);
	अगर (ops->vidioc_g_ext_ctrls == शून्य)
		वापस -ENOTTY;

	ctrls.which = V4L2_CTRL_ID2WHICH(p->id);
	ctrls.count = 1;
	ctrls.controls = &ctrl;
	ctrl.id = p->id;
	ctrl.value = p->value;
	अगर (check_ext_ctrls(&ctrls, 1)) अणु
		पूर्णांक ret = ops->vidioc_g_ext_ctrls(file, fh, &ctrls);

		अगर (ret == 0)
			p->value = ctrl.value;
		वापस ret;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक v4l_s_ctrl(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा v4l2_control *p = arg;
	काष्ठा v4l2_fh *vfh =
		test_bit(V4L2_FL_USES_V4L2_FH, &vfd->flags) ? fh : शून्य;
	काष्ठा v4l2_ext_controls ctrls;
	काष्ठा v4l2_ext_control ctrl;

	अगर (vfh && vfh->ctrl_handler)
		वापस v4l2_s_ctrl(vfh, vfh->ctrl_handler, p);
	अगर (vfd->ctrl_handler)
		वापस v4l2_s_ctrl(शून्य, vfd->ctrl_handler, p);
	अगर (ops->vidioc_s_ctrl)
		वापस ops->vidioc_s_ctrl(file, fh, p);
	अगर (ops->vidioc_s_ext_ctrls == शून्य)
		वापस -ENOTTY;

	ctrls.which = V4L2_CTRL_ID2WHICH(p->id);
	ctrls.count = 1;
	ctrls.controls = &ctrl;
	ctrl.id = p->id;
	ctrl.value = p->value;
	अगर (check_ext_ctrls(&ctrls, 1))
		वापस ops->vidioc_s_ext_ctrls(file, fh, &ctrls);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक v4l_g_ext_ctrls(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा v4l2_ext_controls *p = arg;
	काष्ठा v4l2_fh *vfh =
		test_bit(V4L2_FL_USES_V4L2_FH, &vfd->flags) ? fh : शून्य;

	p->error_idx = p->count;
	अगर (vfh && vfh->ctrl_handler)
		वापस v4l2_g_ext_ctrls(vfh->ctrl_handler,
					vfd, vfd->v4l2_dev->mdev, p);
	अगर (vfd->ctrl_handler)
		वापस v4l2_g_ext_ctrls(vfd->ctrl_handler,
					vfd, vfd->v4l2_dev->mdev, p);
	अगर (ops->vidioc_g_ext_ctrls == शून्य)
		वापस -ENOTTY;
	वापस check_ext_ctrls(p, 0) ? ops->vidioc_g_ext_ctrls(file, fh, p) :
					-EINVAL;
पूर्ण

अटल पूर्णांक v4l_s_ext_ctrls(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा v4l2_ext_controls *p = arg;
	काष्ठा v4l2_fh *vfh =
		test_bit(V4L2_FL_USES_V4L2_FH, &vfd->flags) ? fh : शून्य;

	p->error_idx = p->count;
	अगर (vfh && vfh->ctrl_handler)
		वापस v4l2_s_ext_ctrls(vfh, vfh->ctrl_handler,
					vfd, vfd->v4l2_dev->mdev, p);
	अगर (vfd->ctrl_handler)
		वापस v4l2_s_ext_ctrls(शून्य, vfd->ctrl_handler,
					vfd, vfd->v4l2_dev->mdev, p);
	अगर (ops->vidioc_s_ext_ctrls == शून्य)
		वापस -ENOTTY;
	वापस check_ext_ctrls(p, 0) ? ops->vidioc_s_ext_ctrls(file, fh, p) :
					-EINVAL;
पूर्ण

अटल पूर्णांक v4l_try_ext_ctrls(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा v4l2_ext_controls *p = arg;
	काष्ठा v4l2_fh *vfh =
		test_bit(V4L2_FL_USES_V4L2_FH, &vfd->flags) ? fh : शून्य;

	p->error_idx = p->count;
	अगर (vfh && vfh->ctrl_handler)
		वापस v4l2_try_ext_ctrls(vfh->ctrl_handler,
					  vfd, vfd->v4l2_dev->mdev, p);
	अगर (vfd->ctrl_handler)
		वापस v4l2_try_ext_ctrls(vfd->ctrl_handler,
					  vfd, vfd->v4l2_dev->mdev, p);
	अगर (ops->vidioc_try_ext_ctrls == शून्य)
		वापस -ENOTTY;
	वापस check_ext_ctrls(p, 0) ? ops->vidioc_try_ext_ctrls(file, fh, p) :
					-EINVAL;
पूर्ण

/*
 * The selection API specअगरied originally that the _MPLANE buffer types
 * shouldn't be used. The reasons क्रम this are lost in the mists of समय
 * (or just really crappy memories). Regardless, this is really annoying
 * क्रम userspace. So to keep things simple we map _MPLANE buffer types
 * to their 'regular' counterparts beक्रमe calling the driver. And we
 * restore it afterwards. This way applications can use either buffer
 * type and drivers करोn't need to check क्रम both.
 */
अटल पूर्णांक v4l_g_selection(स्थिर काष्ठा v4l2_ioctl_ops *ops,
			   काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा v4l2_selection *p = arg;
	u32 old_type = p->type;
	पूर्णांक ret;

	अगर (p->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		p->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	अन्यथा अगर (p->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		p->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	ret = ops->vidioc_g_selection(file, fh, p);
	p->type = old_type;
	वापस ret;
पूर्ण

अटल पूर्णांक v4l_s_selection(स्थिर काष्ठा v4l2_ioctl_ops *ops,
			   काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा v4l2_selection *p = arg;
	u32 old_type = p->type;
	पूर्णांक ret;

	अगर (p->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		p->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	अन्यथा अगर (p->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		p->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	ret = ops->vidioc_s_selection(file, fh, p);
	p->type = old_type;
	वापस ret;
पूर्ण

अटल पूर्णांक v4l_g_crop(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा v4l2_crop *p = arg;
	काष्ठा v4l2_selection s = अणु
		.type = p->type,
	पूर्ण;
	पूर्णांक ret;

	/* simulate capture crop using selection api */

	/* crop means compose क्रम output devices */
	अगर (V4L2_TYPE_IS_OUTPUT(p->type))
		s.target = V4L2_SEL_TGT_COMPOSE;
	अन्यथा
		s.target = V4L2_SEL_TGT_CROP;

	अगर (test_bit(V4L2_FL_QUIRK_INVERTED_CROP, &vfd->flags))
		s.target = s.target == V4L2_SEL_TGT_COMPOSE ?
			V4L2_SEL_TGT_CROP : V4L2_SEL_TGT_COMPOSE;

	ret = v4l_g_selection(ops, file, fh, &s);

	/* copying results to old काष्ठाure on success */
	अगर (!ret)
		p->c = s.r;
	वापस ret;
पूर्ण

अटल पूर्णांक v4l_s_crop(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा v4l2_crop *p = arg;
	काष्ठा v4l2_selection s = अणु
		.type = p->type,
		.r = p->c,
	पूर्ण;

	/* simulate capture crop using selection api */

	/* crop means compose क्रम output devices */
	अगर (V4L2_TYPE_IS_OUTPUT(p->type))
		s.target = V4L2_SEL_TGT_COMPOSE;
	अन्यथा
		s.target = V4L2_SEL_TGT_CROP;

	अगर (test_bit(V4L2_FL_QUIRK_INVERTED_CROP, &vfd->flags))
		s.target = s.target == V4L2_SEL_TGT_COMPOSE ?
			V4L2_SEL_TGT_CROP : V4L2_SEL_TGT_COMPOSE;

	वापस v4l_s_selection(ops, file, fh, &s);
पूर्ण

अटल पूर्णांक v4l_cropcap(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा v4l2_cropcap *p = arg;
	काष्ठा v4l2_selection s = अणु .type = p->type पूर्ण;
	पूर्णांक ret = 0;

	/* setting trivial pixelaspect */
	p->pixelaspect.numerator = 1;
	p->pixelaspect.denominator = 1;

	अगर (s.type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		s.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	अन्यथा अगर (s.type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		s.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;

	/*
	 * The determine_valid_ioctls() call alपढ़ोy should ensure
	 * that this can never happen, but just in हाल...
	 */
	अगर (WARN_ON(!ops->vidioc_g_selection))
		वापस -ENOTTY;

	अगर (ops->vidioc_g_pixelaspect)
		ret = ops->vidioc_g_pixelaspect(file, fh, s.type,
						&p->pixelaspect);

	/*
	 * Ignore ENOTTY or ENOIOCTLCMD error वापसs, just use the
	 * square pixel aspect ratio in that हाल.
	 */
	अगर (ret && ret != -ENOTTY && ret != -ENOIOCTLCMD)
		वापस ret;

	/* Use g_selection() to fill in the bounds and defrect rectangles */

	/* obtaining bounds */
	अगर (V4L2_TYPE_IS_OUTPUT(p->type))
		s.target = V4L2_SEL_TGT_COMPOSE_BOUNDS;
	अन्यथा
		s.target = V4L2_SEL_TGT_CROP_BOUNDS;

	अगर (test_bit(V4L2_FL_QUIRK_INVERTED_CROP, &vfd->flags))
		s.target = s.target == V4L2_SEL_TGT_COMPOSE_BOUNDS ?
			V4L2_SEL_TGT_CROP_BOUNDS : V4L2_SEL_TGT_COMPOSE_BOUNDS;

	ret = v4l_g_selection(ops, file, fh, &s);
	अगर (ret)
		वापस ret;
	p->bounds = s.r;

	/* obtaining defrect */
	अगर (s.target == V4L2_SEL_TGT_COMPOSE_BOUNDS)
		s.target = V4L2_SEL_TGT_COMPOSE_DEFAULT;
	अन्यथा
		s.target = V4L2_SEL_TGT_CROP_DEFAULT;

	ret = v4l_g_selection(ops, file, fh, &s);
	अगर (ret)
		वापस ret;
	p->defrect = s.r;

	वापस 0;
पूर्ण

अटल पूर्णांक v4l_log_status(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	पूर्णांक ret;

	अगर (vfd->v4l2_dev)
		pr_info("%s: =================  START STATUS  =================\n",
			vfd->v4l2_dev->name);
	ret = ops->vidioc_log_status(file, fh);
	अगर (vfd->v4l2_dev)
		pr_info("%s: ==================  END STATUS  ==================\n",
			vfd->v4l2_dev->name);
	वापस ret;
पूर्ण

अटल पूर्णांक v4l_dbg_g_रेजिस्टर(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	काष्ठा v4l2_dbg_रेजिस्टर *p = arg;
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा v4l2_subdev *sd;
	पूर्णांक idx = 0;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	अगर (p->match.type == V4L2_CHIP_MATCH_SUBDEV) अणु
		अगर (vfd->v4l2_dev == शून्य)
			वापस -EINVAL;
		v4l2_device_क्रम_each_subdev(sd, vfd->v4l2_dev)
			अगर (p->match.addr == idx++)
				वापस v4l2_subdev_call(sd, core, g_रेजिस्टर, p);
		वापस -EINVAL;
	पूर्ण
	अगर (ops->vidioc_g_रेजिस्टर && p->match.type == V4L2_CHIP_MATCH_BRIDGE &&
	    (ops->vidioc_g_chip_info || p->match.addr == 0))
		वापस ops->vidioc_g_रेजिस्टर(file, fh, p);
	वापस -EINVAL;
#अन्यथा
	वापस -ENOTTY;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक v4l_dbg_s_रेजिस्टर(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	स्थिर काष्ठा v4l2_dbg_रेजिस्टर *p = arg;
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा v4l2_subdev *sd;
	पूर्णांक idx = 0;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	अगर (p->match.type == V4L2_CHIP_MATCH_SUBDEV) अणु
		अगर (vfd->v4l2_dev == शून्य)
			वापस -EINVAL;
		v4l2_device_क्रम_each_subdev(sd, vfd->v4l2_dev)
			अगर (p->match.addr == idx++)
				वापस v4l2_subdev_call(sd, core, s_रेजिस्टर, p);
		वापस -EINVAL;
	पूर्ण
	अगर (ops->vidioc_s_रेजिस्टर && p->match.type == V4L2_CHIP_MATCH_BRIDGE &&
	    (ops->vidioc_g_chip_info || p->match.addr == 0))
		वापस ops->vidioc_s_रेजिस्टर(file, fh, p);
	वापस -EINVAL;
#अन्यथा
	वापस -ENOTTY;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक v4l_dbg_g_chip_info(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा v4l2_dbg_chip_info *p = arg;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक idx = 0;

	चयन (p->match.type) अणु
	हाल V4L2_CHIP_MATCH_BRIDGE:
		अगर (ops->vidioc_s_रेजिस्टर)
			p->flags |= V4L2_CHIP_FL_WRITABLE;
		अगर (ops->vidioc_g_रेजिस्टर)
			p->flags |= V4L2_CHIP_FL_READABLE;
		strscpy(p->name, vfd->v4l2_dev->name, माप(p->name));
		अगर (ops->vidioc_g_chip_info)
			वापस ops->vidioc_g_chip_info(file, fh, arg);
		अगर (p->match.addr)
			वापस -EINVAL;
		वापस 0;

	हाल V4L2_CHIP_MATCH_SUBDEV:
		अगर (vfd->v4l2_dev == शून्य)
			अवरोध;
		v4l2_device_क्रम_each_subdev(sd, vfd->v4l2_dev) अणु
			अगर (p->match.addr != idx++)
				जारी;
			अगर (sd->ops->core && sd->ops->core->s_रेजिस्टर)
				p->flags |= V4L2_CHIP_FL_WRITABLE;
			अगर (sd->ops->core && sd->ops->core->g_रेजिस्टर)
				p->flags |= V4L2_CHIP_FL_READABLE;
			strscpy(p->name, sd->name, माप(p->name));
			वापस 0;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस -EINVAL;
#अन्यथा
	वापस -ENOTTY;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक v4l_dqevent(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	वापस v4l2_event_dequeue(fh, arg, file->f_flags & O_NONBLOCK);
पूर्ण

अटल पूर्णांक v4l_subscribe_event(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	वापस ops->vidioc_subscribe_event(fh, arg);
पूर्ण

अटल पूर्णांक v4l_unsubscribe_event(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	वापस ops->vidioc_unsubscribe_event(fh, arg);
पूर्ण

अटल पूर्णांक v4l_g_sliced_vbi_cap(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा v4l2_sliced_vbi_cap *p = arg;
	पूर्णांक ret = check_fmt(file, p->type);

	अगर (ret)
		वापस ret;

	/* Clear up to type, everything after type is zeroed alपढ़ोy */
	स_रखो(p, 0, दुरत्व(काष्ठा v4l2_sliced_vbi_cap, type));

	वापस ops->vidioc_g_sliced_vbi_cap(file, fh, p);
पूर्ण

अटल पूर्णांक v4l_क्रमागत_freq_bands(स्थिर काष्ठा v4l2_ioctl_ops *ops,
				काष्ठा file *file, व्योम *fh, व्योम *arg)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा v4l2_frequency_band *p = arg;
	क्रमागत v4l2_tuner_type type;
	पूर्णांक err;

	अगर (vfd->vfl_type == VFL_TYPE_SDR) अणु
		अगर (p->type != V4L2_TUNER_SDR && p->type != V4L2_TUNER_RF)
			वापस -EINVAL;
		type = p->type;
	पूर्ण अन्यथा अणु
		type = (vfd->vfl_type == VFL_TYPE_RADIO) ?
				V4L2_TUNER_RADIO : V4L2_TUNER_ANALOG_TV;
		अगर (type != p->type)
			वापस -EINVAL;
	पूर्ण
	अगर (ops->vidioc_क्रमागत_freq_bands) अणु
		err = ops->vidioc_क्रमागत_freq_bands(file, fh, p);
		अगर (err != -ENOTTY)
			वापस err;
	पूर्ण
	अगर (is_valid_ioctl(vfd, VIDIOC_G_TUNER)) अणु
		काष्ठा v4l2_tuner t = अणु
			.index = p->tuner,
			.type = type,
		पूर्ण;

		अगर (p->index)
			वापस -EINVAL;
		err = ops->vidioc_g_tuner(file, fh, &t);
		अगर (err)
			वापस err;
		p->capability = t.capability | V4L2_TUNER_CAP_FREQ_BANDS;
		p->rangelow = t.rangelow;
		p->rangehigh = t.rangehigh;
		p->modulation = (type == V4L2_TUNER_RADIO) ?
			V4L2_BAND_MODULATION_FM : V4L2_BAND_MODULATION_VSB;
		वापस 0;
	पूर्ण
	अगर (is_valid_ioctl(vfd, VIDIOC_G_MODULATOR)) अणु
		काष्ठा v4l2_modulator m = अणु
			.index = p->tuner,
		पूर्ण;

		अगर (type != V4L2_TUNER_RADIO)
			वापस -EINVAL;
		अगर (p->index)
			वापस -EINVAL;
		err = ops->vidioc_g_modulator(file, fh, &m);
		अगर (err)
			वापस err;
		p->capability = m.capability | V4L2_TUNER_CAP_FREQ_BANDS;
		p->rangelow = m.rangelow;
		p->rangehigh = m.rangehigh;
		p->modulation = (type == V4L2_TUNER_RADIO) ?
			V4L2_BAND_MODULATION_FM : V4L2_BAND_MODULATION_VSB;
		वापस 0;
	पूर्ण
	वापस -ENOTTY;
पूर्ण

काष्ठा v4l2_ioctl_info अणु
	अचिन्हित पूर्णांक ioctl;
	u32 flags;
	स्थिर अक्षर * स्थिर name;
	पूर्णांक (*func)(स्थिर काष्ठा v4l2_ioctl_ops *ops, काष्ठा file *file,
		    व्योम *fh, व्योम *p);
	व्योम (*debug)(स्थिर व्योम *arg, bool ग_लिखो_only);
पूर्ण;

/* This control needs a priority check */
#घोषणा INFO_FL_PRIO		(1 << 0)
/* This control can be valid अगर the filehandle passes a control handler. */
#घोषणा INFO_FL_CTRL		(1 << 1)
/* Queuing ioctl */
#घोषणा INFO_FL_QUEUE		(1 << 2)
/* Always copy back result, even on error */
#घोषणा INFO_FL_ALWAYS_COPY	(1 << 3)
/* Zero काष्ठा from after the field to the end */
#घोषणा INFO_FL_CLEAR(v4l2_काष्ठा, field)			\
	((दुरत्व(काष्ठा v4l2_काष्ठा, field) +			\
	  माप_field(काष्ठा v4l2_काष्ठा, field)) << 16)
#घोषणा INFO_FL_CLEAR_MASK	(_IOC_SIZEMASK << 16)

#घोषणा DEFINE_V4L_STUB_FUNC(_vidioc)				\
	अटल पूर्णांक v4l_stub_ ## _vidioc(			\
			स्थिर काष्ठा v4l2_ioctl_ops *ops,	\
			काष्ठा file *file, व्योम *fh, व्योम *p)	\
	अणु							\
		वापस ops->vidioc_ ## _vidioc(file, fh, p);	\
	पूर्ण

#घोषणा IOCTL_INFO(_ioctl, _func, _debug, _flags)		\
	[_IOC_NR(_ioctl)] = अणु					\
		.ioctl = _ioctl,				\
		.flags = _flags,				\
		.name = #_ioctl,				\
		.func = _func,					\
		.debug = _debug,				\
	पूर्ण

DEFINE_V4L_STUB_FUNC(g_fbuf)
DEFINE_V4L_STUB_FUNC(s_fbuf)
DEFINE_V4L_STUB_FUNC(expbuf)
DEFINE_V4L_STUB_FUNC(g_std)
DEFINE_V4L_STUB_FUNC(g_audio)
DEFINE_V4L_STUB_FUNC(s_audio)
DEFINE_V4L_STUB_FUNC(g_edid)
DEFINE_V4L_STUB_FUNC(s_edid)
DEFINE_V4L_STUB_FUNC(g_auकरोut)
DEFINE_V4L_STUB_FUNC(s_auकरोut)
DEFINE_V4L_STUB_FUNC(g_jpegcomp)
DEFINE_V4L_STUB_FUNC(s_jpegcomp)
DEFINE_V4L_STUB_FUNC(क्रमागतaudio)
DEFINE_V4L_STUB_FUNC(क्रमागतauकरोut)
DEFINE_V4L_STUB_FUNC(क्रमागत_framesizes)
DEFINE_V4L_STUB_FUNC(क्रमागत_frameपूर्णांकervals)
DEFINE_V4L_STUB_FUNC(g_enc_index)
DEFINE_V4L_STUB_FUNC(encoder_cmd)
DEFINE_V4L_STUB_FUNC(try_encoder_cmd)
DEFINE_V4L_STUB_FUNC(decoder_cmd)
DEFINE_V4L_STUB_FUNC(try_decoder_cmd)
DEFINE_V4L_STUB_FUNC(s_dv_timings)
DEFINE_V4L_STUB_FUNC(g_dv_timings)
DEFINE_V4L_STUB_FUNC(क्रमागत_dv_timings)
DEFINE_V4L_STUB_FUNC(query_dv_timings)
DEFINE_V4L_STUB_FUNC(dv_timings_cap)

अटल स्थिर काष्ठा v4l2_ioctl_info v4l2_ioctls[] = अणु
	IOCTL_INFO(VIDIOC_QUERYCAP, v4l_querycap, v4l_prपूर्णांक_querycap, 0),
	IOCTL_INFO(VIDIOC_ENUM_FMT, v4l_क्रमागत_fmt, v4l_prपूर्णांक_fmtdesc, 0),
	IOCTL_INFO(VIDIOC_G_FMT, v4l_g_fmt, v4l_prपूर्णांक_क्रमmat, 0),
	IOCTL_INFO(VIDIOC_S_FMT, v4l_s_fmt, v4l_prपूर्णांक_क्रमmat, INFO_FL_PRIO),
	IOCTL_INFO(VIDIOC_REQBUFS, v4l_reqbufs, v4l_prपूर्णांक_requestbuffers, INFO_FL_PRIO | INFO_FL_QUEUE),
	IOCTL_INFO(VIDIOC_QUERYBUF, v4l_querybuf, v4l_prपूर्णांक_buffer, INFO_FL_QUEUE | INFO_FL_CLEAR(v4l2_buffer, length)),
	IOCTL_INFO(VIDIOC_G_FBUF, v4l_stub_g_fbuf, v4l_prपूर्णांक_framebuffer, 0),
	IOCTL_INFO(VIDIOC_S_FBUF, v4l_stub_s_fbuf, v4l_prपूर्णांक_framebuffer, INFO_FL_PRIO),
	IOCTL_INFO(VIDIOC_OVERLAY, v4l_overlay, v4l_prपूर्णांक_u32, INFO_FL_PRIO),
	IOCTL_INFO(VIDIOC_QBUF, v4l_qbuf, v4l_prपूर्णांक_buffer, INFO_FL_QUEUE),
	IOCTL_INFO(VIDIOC_EXPBUF, v4l_stub_expbuf, v4l_prपूर्णांक_exportbuffer, INFO_FL_QUEUE | INFO_FL_CLEAR(v4l2_exportbuffer, flags)),
	IOCTL_INFO(VIDIOC_DQBUF, v4l_dqbuf, v4l_prपूर्णांक_buffer, INFO_FL_QUEUE),
	IOCTL_INFO(VIDIOC_STREAMON, v4l_streamon, v4l_prपूर्णांक_buftype, INFO_FL_PRIO | INFO_FL_QUEUE),
	IOCTL_INFO(VIDIOC_STREAMOFF, v4l_streamoff, v4l_prपूर्णांक_buftype, INFO_FL_PRIO | INFO_FL_QUEUE),
	IOCTL_INFO(VIDIOC_G_PARM, v4l_g_parm, v4l_prपूर्णांक_streamparm, INFO_FL_CLEAR(v4l2_streamparm, type)),
	IOCTL_INFO(VIDIOC_S_PARM, v4l_s_parm, v4l_prपूर्णांक_streamparm, INFO_FL_PRIO),
	IOCTL_INFO(VIDIOC_G_STD, v4l_stub_g_std, v4l_prपूर्णांक_std, 0),
	IOCTL_INFO(VIDIOC_S_STD, v4l_s_std, v4l_prपूर्णांक_std, INFO_FL_PRIO),
	IOCTL_INFO(VIDIOC_ENUMSTD, v4l_क्रमागतstd, v4l_prपूर्णांक_standard, INFO_FL_CLEAR(v4l2_standard, index)),
	IOCTL_INFO(VIDIOC_ENUMINPUT, v4l_क्रमागतinput, v4l_prपूर्णांक_क्रमागतinput, INFO_FL_CLEAR(v4l2_input, index)),
	IOCTL_INFO(VIDIOC_G_CTRL, v4l_g_ctrl, v4l_prपूर्णांक_control, INFO_FL_CTRL | INFO_FL_CLEAR(v4l2_control, id)),
	IOCTL_INFO(VIDIOC_S_CTRL, v4l_s_ctrl, v4l_prपूर्णांक_control, INFO_FL_PRIO | INFO_FL_CTRL),
	IOCTL_INFO(VIDIOC_G_TUNER, v4l_g_tuner, v4l_prपूर्णांक_tuner, INFO_FL_CLEAR(v4l2_tuner, index)),
	IOCTL_INFO(VIDIOC_S_TUNER, v4l_s_tuner, v4l_prपूर्णांक_tuner, INFO_FL_PRIO),
	IOCTL_INFO(VIDIOC_G_AUDIO, v4l_stub_g_audio, v4l_prपूर्णांक_audio, 0),
	IOCTL_INFO(VIDIOC_S_AUDIO, v4l_stub_s_audio, v4l_prपूर्णांक_audio, INFO_FL_PRIO),
	IOCTL_INFO(VIDIOC_QUERYCTRL, v4l_queryctrl, v4l_prपूर्णांक_queryctrl, INFO_FL_CTRL | INFO_FL_CLEAR(v4l2_queryctrl, id)),
	IOCTL_INFO(VIDIOC_QUERYMENU, v4l_querymenu, v4l_prपूर्णांक_querymenu, INFO_FL_CTRL | INFO_FL_CLEAR(v4l2_querymenu, index)),
	IOCTL_INFO(VIDIOC_G_INPUT, v4l_g_input, v4l_prपूर्णांक_u32, 0),
	IOCTL_INFO(VIDIOC_S_INPUT, v4l_s_input, v4l_prपूर्णांक_u32, INFO_FL_PRIO),
	IOCTL_INFO(VIDIOC_G_EDID, v4l_stub_g_edid, v4l_prपूर्णांक_edid, INFO_FL_ALWAYS_COPY),
	IOCTL_INFO(VIDIOC_S_EDID, v4l_stub_s_edid, v4l_prपूर्णांक_edid, INFO_FL_PRIO | INFO_FL_ALWAYS_COPY),
	IOCTL_INFO(VIDIOC_G_OUTPUT, v4l_g_output, v4l_prपूर्णांक_u32, 0),
	IOCTL_INFO(VIDIOC_S_OUTPUT, v4l_s_output, v4l_prपूर्णांक_u32, INFO_FL_PRIO),
	IOCTL_INFO(VIDIOC_ENUMOUTPUT, v4l_क्रमागतoutput, v4l_prपूर्णांक_क्रमागतoutput, INFO_FL_CLEAR(v4l2_output, index)),
	IOCTL_INFO(VIDIOC_G_AUDOUT, v4l_stub_g_auकरोut, v4l_prपूर्णांक_audioout, 0),
	IOCTL_INFO(VIDIOC_S_AUDOUT, v4l_stub_s_auकरोut, v4l_prपूर्णांक_audioout, INFO_FL_PRIO),
	IOCTL_INFO(VIDIOC_G_MODULATOR, v4l_g_modulator, v4l_prपूर्णांक_modulator, INFO_FL_CLEAR(v4l2_modulator, index)),
	IOCTL_INFO(VIDIOC_S_MODULATOR, v4l_s_modulator, v4l_prपूर्णांक_modulator, INFO_FL_PRIO),
	IOCTL_INFO(VIDIOC_G_FREQUENCY, v4l_g_frequency, v4l_prपूर्णांक_frequency, INFO_FL_CLEAR(v4l2_frequency, tuner)),
	IOCTL_INFO(VIDIOC_S_FREQUENCY, v4l_s_frequency, v4l_prपूर्णांक_frequency, INFO_FL_PRIO),
	IOCTL_INFO(VIDIOC_CROPCAP, v4l_cropcap, v4l_prपूर्णांक_cropcap, INFO_FL_CLEAR(v4l2_cropcap, type)),
	IOCTL_INFO(VIDIOC_G_CROP, v4l_g_crop, v4l_prपूर्णांक_crop, INFO_FL_CLEAR(v4l2_crop, type)),
	IOCTL_INFO(VIDIOC_S_CROP, v4l_s_crop, v4l_prपूर्णांक_crop, INFO_FL_PRIO),
	IOCTL_INFO(VIDIOC_G_SELECTION, v4l_g_selection, v4l_prपूर्णांक_selection, INFO_FL_CLEAR(v4l2_selection, r)),
	IOCTL_INFO(VIDIOC_S_SELECTION, v4l_s_selection, v4l_prपूर्णांक_selection, INFO_FL_PRIO | INFO_FL_CLEAR(v4l2_selection, r)),
	IOCTL_INFO(VIDIOC_G_JPEGCOMP, v4l_stub_g_jpegcomp, v4l_prपूर्णांक_jpegcompression, 0),
	IOCTL_INFO(VIDIOC_S_JPEGCOMP, v4l_stub_s_jpegcomp, v4l_prपूर्णांक_jpegcompression, INFO_FL_PRIO),
	IOCTL_INFO(VIDIOC_QUERYSTD, v4l_querystd, v4l_prपूर्णांक_std, 0),
	IOCTL_INFO(VIDIOC_TRY_FMT, v4l_try_fmt, v4l_prपूर्णांक_क्रमmat, 0),
	IOCTL_INFO(VIDIOC_ENUMAUDIO, v4l_stub_क्रमागतaudio, v4l_prपूर्णांक_audio, INFO_FL_CLEAR(v4l2_audio, index)),
	IOCTL_INFO(VIDIOC_ENUMAUDOUT, v4l_stub_क्रमागतauकरोut, v4l_prपूर्णांक_audioout, INFO_FL_CLEAR(v4l2_audioout, index)),
	IOCTL_INFO(VIDIOC_G_PRIORITY, v4l_g_priority, v4l_prपूर्णांक_u32, 0),
	IOCTL_INFO(VIDIOC_S_PRIORITY, v4l_s_priority, v4l_prपूर्णांक_u32, INFO_FL_PRIO),
	IOCTL_INFO(VIDIOC_G_SLICED_VBI_CAP, v4l_g_sliced_vbi_cap, v4l_prपूर्णांक_sliced_vbi_cap, INFO_FL_CLEAR(v4l2_sliced_vbi_cap, type)),
	IOCTL_INFO(VIDIOC_LOG_STATUS, v4l_log_status, v4l_prपूर्णांक_newline, 0),
	IOCTL_INFO(VIDIOC_G_EXT_CTRLS, v4l_g_ext_ctrls, v4l_prपूर्णांक_ext_controls, INFO_FL_CTRL),
	IOCTL_INFO(VIDIOC_S_EXT_CTRLS, v4l_s_ext_ctrls, v4l_prपूर्णांक_ext_controls, INFO_FL_PRIO | INFO_FL_CTRL),
	IOCTL_INFO(VIDIOC_TRY_EXT_CTRLS, v4l_try_ext_ctrls, v4l_prपूर्णांक_ext_controls, INFO_FL_CTRL),
	IOCTL_INFO(VIDIOC_ENUM_FRAMESIZES, v4l_stub_क्रमागत_framesizes, v4l_prपूर्णांक_frmsizeक्रमागत, INFO_FL_CLEAR(v4l2_frmsizeक्रमागत, pixel_क्रमmat)),
	IOCTL_INFO(VIDIOC_ENUM_FRAMEINTERVALS, v4l_stub_क्रमागत_frameपूर्णांकervals, v4l_prपूर्णांक_frmivalक्रमागत, INFO_FL_CLEAR(v4l2_frmivalक्रमागत, height)),
	IOCTL_INFO(VIDIOC_G_ENC_INDEX, v4l_stub_g_enc_index, v4l_prपूर्णांक_enc_idx, 0),
	IOCTL_INFO(VIDIOC_ENCODER_CMD, v4l_stub_encoder_cmd, v4l_prपूर्णांक_encoder_cmd, INFO_FL_PRIO | INFO_FL_CLEAR(v4l2_encoder_cmd, flags)),
	IOCTL_INFO(VIDIOC_TRY_ENCODER_CMD, v4l_stub_try_encoder_cmd, v4l_prपूर्णांक_encoder_cmd, INFO_FL_CLEAR(v4l2_encoder_cmd, flags)),
	IOCTL_INFO(VIDIOC_DECODER_CMD, v4l_stub_decoder_cmd, v4l_prपूर्णांक_decoder_cmd, INFO_FL_PRIO),
	IOCTL_INFO(VIDIOC_TRY_DECODER_CMD, v4l_stub_try_decoder_cmd, v4l_prपूर्णांक_decoder_cmd, 0),
	IOCTL_INFO(VIDIOC_DBG_S_REGISTER, v4l_dbg_s_रेजिस्टर, v4l_prपूर्णांक_dbg_रेजिस्टर, 0),
	IOCTL_INFO(VIDIOC_DBG_G_REGISTER, v4l_dbg_g_रेजिस्टर, v4l_prपूर्णांक_dbg_रेजिस्टर, 0),
	IOCTL_INFO(VIDIOC_S_HW_FREQ_SEEK, v4l_s_hw_freq_seek, v4l_prपूर्णांक_hw_freq_seek, INFO_FL_PRIO),
	IOCTL_INFO(VIDIOC_S_DV_TIMINGS, v4l_stub_s_dv_timings, v4l_prपूर्णांक_dv_timings, INFO_FL_PRIO | INFO_FL_CLEAR(v4l2_dv_timings, bt.flags)),
	IOCTL_INFO(VIDIOC_G_DV_TIMINGS, v4l_stub_g_dv_timings, v4l_prपूर्णांक_dv_timings, 0),
	IOCTL_INFO(VIDIOC_DQEVENT, v4l_dqevent, v4l_prपूर्णांक_event, 0),
	IOCTL_INFO(VIDIOC_SUBSCRIBE_EVENT, v4l_subscribe_event, v4l_prपूर्णांक_event_subscription, 0),
	IOCTL_INFO(VIDIOC_UNSUBSCRIBE_EVENT, v4l_unsubscribe_event, v4l_prपूर्णांक_event_subscription, 0),
	IOCTL_INFO(VIDIOC_CREATE_BUFS, v4l_create_bufs, v4l_prपूर्णांक_create_buffers, INFO_FL_PRIO | INFO_FL_QUEUE),
	IOCTL_INFO(VIDIOC_PREPARE_BUF, v4l_prepare_buf, v4l_prपूर्णांक_buffer, INFO_FL_QUEUE),
	IOCTL_INFO(VIDIOC_ENUM_DV_TIMINGS, v4l_stub_क्रमागत_dv_timings, v4l_prपूर्णांक_क्रमागत_dv_timings, INFO_FL_CLEAR(v4l2_क्रमागत_dv_timings, pad)),
	IOCTL_INFO(VIDIOC_QUERY_DV_TIMINGS, v4l_stub_query_dv_timings, v4l_prपूर्णांक_dv_timings, INFO_FL_ALWAYS_COPY),
	IOCTL_INFO(VIDIOC_DV_TIMINGS_CAP, v4l_stub_dv_timings_cap, v4l_prपूर्णांक_dv_timings_cap, INFO_FL_CLEAR(v4l2_dv_timings_cap, pad)),
	IOCTL_INFO(VIDIOC_ENUM_FREQ_BANDS, v4l_क्रमागत_freq_bands, v4l_prपूर्णांक_freq_band, 0),
	IOCTL_INFO(VIDIOC_DBG_G_CHIP_INFO, v4l_dbg_g_chip_info, v4l_prपूर्णांक_dbg_chip_info, INFO_FL_CLEAR(v4l2_dbg_chip_info, match)),
	IOCTL_INFO(VIDIOC_QUERY_EXT_CTRL, v4l_query_ext_ctrl, v4l_prपूर्णांक_query_ext_ctrl, INFO_FL_CTRL | INFO_FL_CLEAR(v4l2_query_ext_ctrl, id)),
पूर्ण;
#घोषणा V4L2_IOCTLS ARRAY_SIZE(v4l2_ioctls)

अटल bool v4l2_is_known_ioctl(अचिन्हित पूर्णांक cmd)
अणु
	अगर (_IOC_NR(cmd) >= V4L2_IOCTLS)
		वापस false;
	वापस v4l2_ioctls[_IOC_NR(cmd)].ioctl == cmd;
पूर्ण

अटल काष्ठा mutex *v4l2_ioctl_get_lock(काष्ठा video_device *vdev,
					 काष्ठा v4l2_fh *vfh, अचिन्हित पूर्णांक cmd,
					 व्योम *arg)
अणु
	अगर (_IOC_NR(cmd) >= V4L2_IOCTLS)
		वापस vdev->lock;
	अगर (vfh && vfh->m2m_ctx &&
	    (v4l2_ioctls[_IOC_NR(cmd)].flags & INFO_FL_QUEUE)) अणु
		अगर (vfh->m2m_ctx->q_lock)
			वापस vfh->m2m_ctx->q_lock;
	पूर्ण
	अगर (vdev->queue && vdev->queue->lock &&
			(v4l2_ioctls[_IOC_NR(cmd)].flags & INFO_FL_QUEUE))
		वापस vdev->queue->lock;
	वापस vdev->lock;
पूर्ण

/* Common ioctl debug function. This function can be used by
   बाह्यal ioctl messages as well as पूर्णांकernal V4L ioctl */
व्योम v4l_prपूर्णांकk_ioctl(स्थिर अक्षर *prefix, अचिन्हित पूर्णांक cmd)
अणु
	स्थिर अक्षर *dir, *type;

	अगर (prefix)
		prपूर्णांकk(KERN_DEBUG "%s: ", prefix);

	चयन (_IOC_TYPE(cmd)) अणु
	हाल 'd':
		type = "v4l2_int";
		अवरोध;
	हाल 'V':
		अगर (_IOC_NR(cmd) >= V4L2_IOCTLS) अणु
			type = "v4l2";
			अवरोध;
		पूर्ण
		pr_cont("%s", v4l2_ioctls[_IOC_NR(cmd)].name);
		वापस;
	शेष:
		type = "unknown";
		अवरोध;
	पूर्ण

	चयन (_IOC_सूची(cmd)) अणु
	हाल _IOC_NONE:              dir = "--"; अवरोध;
	हाल _IOC_READ:              dir = "r-"; अवरोध;
	हाल _IOC_WRITE:             dir = "-w"; अवरोध;
	हाल _IOC_READ | _IOC_WRITE: dir = "rw"; अवरोध;
	शेष:                     dir = "*ERR*"; अवरोध;
	पूर्ण
	pr_cont("%s ioctl '%c', dir=%s, #%d (0x%08x)",
		type, _IOC_TYPE(cmd), dir, _IOC_NR(cmd), cmd);
पूर्ण
EXPORT_SYMBOL(v4l_prपूर्णांकk_ioctl);

अटल दीर्घ __video_करो_ioctl(काष्ठा file *file,
		अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा mutex *req_queue_lock = शून्य;
	काष्ठा mutex *lock; /* ioctl serialization mutex */
	स्थिर काष्ठा v4l2_ioctl_ops *ops = vfd->ioctl_ops;
	bool ग_लिखो_only = false;
	काष्ठा v4l2_ioctl_info शेष_info;
	स्थिर काष्ठा v4l2_ioctl_info *info;
	व्योम *fh = file->निजी_data;
	काष्ठा v4l2_fh *vfh = शून्य;
	पूर्णांक dev_debug = vfd->dev_debug;
	दीर्घ ret = -ENOTTY;

	अगर (ops == शून्य) अणु
		pr_warn("%s: has no ioctl_ops.\n",
				video_device_node_name(vfd));
		वापस ret;
	पूर्ण

	अगर (test_bit(V4L2_FL_USES_V4L2_FH, &vfd->flags))
		vfh = file->निजी_data;

	/*
	 * We need to serialize streamon/off with queueing new requests.
	 * These ioctls may trigger the cancellation of a streaming
	 * operation, and that should not be mixed with queueing a new
	 * request at the same समय.
	 */
	अगर (v4l2_device_supports_requests(vfd->v4l2_dev) &&
	    (cmd == VIDIOC_STREAMON || cmd == VIDIOC_STREAMOFF)) अणु
		req_queue_lock = &vfd->v4l2_dev->mdev->req_queue_mutex;

		अगर (mutex_lock_पूर्णांकerruptible(req_queue_lock))
			वापस -ERESTARTSYS;
	पूर्ण

	lock = v4l2_ioctl_get_lock(vfd, vfh, cmd, arg);

	अगर (lock && mutex_lock_पूर्णांकerruptible(lock)) अणु
		अगर (req_queue_lock)
			mutex_unlock(req_queue_lock);
		वापस -ERESTARTSYS;
	पूर्ण

	अगर (!video_is_रेजिस्टरed(vfd)) अणु
		ret = -ENODEV;
		जाओ unlock;
	पूर्ण

	अगर (v4l2_is_known_ioctl(cmd)) अणु
		info = &v4l2_ioctls[_IOC_NR(cmd)];

		अगर (!test_bit(_IOC_NR(cmd), vfd->valid_ioctls) &&
		    !((info->flags & INFO_FL_CTRL) && vfh && vfh->ctrl_handler))
			जाओ करोne;

		अगर (vfh && (info->flags & INFO_FL_PRIO)) अणु
			ret = v4l2_prio_check(vfd->prio, vfh->prio);
			अगर (ret)
				जाओ करोne;
		पूर्ण
	पूर्ण अन्यथा अणु
		शेष_info.ioctl = cmd;
		शेष_info.flags = 0;
		शेष_info.debug = v4l_prपूर्णांक_शेष;
		info = &शेष_info;
	पूर्ण

	ग_लिखो_only = _IOC_सूची(cmd) == _IOC_WRITE;
	अगर (info != &शेष_info) अणु
		ret = info->func(ops, file, fh, arg);
	पूर्ण अन्यथा अगर (!ops->vidioc_शेष) अणु
		ret = -ENOTTY;
	पूर्ण अन्यथा अणु
		ret = ops->vidioc_शेष(file, fh,
			vfh ? v4l2_prio_check(vfd->prio, vfh->prio) >= 0 : 0,
			cmd, arg);
	पूर्ण

करोne:
	अगर (dev_debug & (V4L2_DEV_DEBUG_IOCTL | V4L2_DEV_DEBUG_IOCTL_ARG)) अणु
		अगर (!(dev_debug & V4L2_DEV_DEBUG_STREAMING) &&
		    (cmd == VIDIOC_QBUF || cmd == VIDIOC_DQBUF))
			जाओ unlock;

		v4l_prपूर्णांकk_ioctl(video_device_node_name(vfd), cmd);
		अगर (ret < 0)
			pr_cont(": error %ld", ret);
		अगर (!(dev_debug & V4L2_DEV_DEBUG_IOCTL_ARG))
			pr_cont("\n");
		अन्यथा अगर (_IOC_सूची(cmd) == _IOC_NONE)
			info->debug(arg, ग_लिखो_only);
		अन्यथा अणु
			pr_cont(": ");
			info->debug(arg, ग_लिखो_only);
		पूर्ण
	पूर्ण

unlock:
	अगर (lock)
		mutex_unlock(lock);
	अगर (req_queue_lock)
		mutex_unlock(req_queue_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक check_array_args(अचिन्हित पूर्णांक cmd, व्योम *parg, माप_प्रकार *array_size,
			    व्योम __user **user_ptr, व्योम ***kernel_ptr)
अणु
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल VIDIOC_PREPARE_BUF:
	हाल VIDIOC_QUERYBUF:
	हाल VIDIOC_QBUF:
	हाल VIDIOC_DQBUF: अणु
		काष्ठा v4l2_buffer *buf = parg;

		अगर (V4L2_TYPE_IS_MULTIPLANAR(buf->type) && buf->length > 0) अणु
			अगर (buf->length > VIDEO_MAX_PLANES) अणु
				ret = -EINVAL;
				अवरोध;
			पूर्ण
			*user_ptr = (व्योम __user *)buf->m.planes;
			*kernel_ptr = (व्योम **)&buf->m.planes;
			*array_size = माप(काष्ठा v4l2_plane) * buf->length;
			ret = 1;
		पूर्ण
		अवरोध;
	पूर्ण

	हाल VIDIOC_G_EDID:
	हाल VIDIOC_S_EDID: अणु
		काष्ठा v4l2_edid *edid = parg;

		अगर (edid->blocks) अणु
			अगर (edid->blocks > 256) अणु
				ret = -EINVAL;
				अवरोध;
			पूर्ण
			*user_ptr = (व्योम __user *)edid->edid;
			*kernel_ptr = (व्योम **)&edid->edid;
			*array_size = edid->blocks * 128;
			ret = 1;
		पूर्ण
		अवरोध;
	पूर्ण

	हाल VIDIOC_S_EXT_CTRLS:
	हाल VIDIOC_G_EXT_CTRLS:
	हाल VIDIOC_TRY_EXT_CTRLS: अणु
		काष्ठा v4l2_ext_controls *ctrls = parg;

		अगर (ctrls->count != 0) अणु
			अगर (ctrls->count > V4L2_CID_MAX_CTRLS) अणु
				ret = -EINVAL;
				अवरोध;
			पूर्ण
			*user_ptr = (व्योम __user *)ctrls->controls;
			*kernel_ptr = (व्योम **)&ctrls->controls;
			*array_size = माप(काष्ठा v4l2_ext_control)
				    * ctrls->count;
			ret = 1;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल VIDIOC_G_FMT:
	हाल VIDIOC_S_FMT:
	हाल VIDIOC_TRY_FMT: अणु
		काष्ठा v4l2_क्रमmat *fmt = parg;

		अगर (fmt->type != V4L2_BUF_TYPE_VIDEO_OVERLAY &&
		    fmt->type != V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY)
			अवरोध;
		अगर (fmt->fmt.win.clipcount > 2048)
			वापस -EINVAL;
		अगर (!fmt->fmt.win.clipcount)
			अवरोध;

		*user_ptr = (व्योम __user *)fmt->fmt.win.clips;
		*kernel_ptr = (व्योम **)&fmt->fmt.win.clips;
		*array_size = माप(काष्ठा v4l2_clip)
				* fmt->fmt.win.clipcount;

		ret = 1;
		अवरोध;
	पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक video_translate_cmd(अचिन्हित पूर्णांक cmd)
अणु
	चयन (cmd) अणु
#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
	हाल VIDIOC_DQEVENT_TIME32:
		वापस VIDIOC_DQEVENT;
	हाल VIDIOC_QUERYBUF_TIME32:
		वापस VIDIOC_QUERYBUF;
	हाल VIDIOC_QBUF_TIME32:
		वापस VIDIOC_QBUF;
	हाल VIDIOC_DQBUF_TIME32:
		वापस VIDIOC_DQBUF;
	हाल VIDIOC_PREPARE_BUF_TIME32:
		वापस VIDIOC_PREPARE_BUF;
#पूर्ण_अगर
	पूर्ण
	अगर (in_compat_syscall())
		वापस v4l2_compat_translate_cmd(cmd);

	वापस cmd;
पूर्ण

अटल पूर्णांक video_get_user(व्योम __user *arg, व्योम *parg,
			  अचिन्हित पूर्णांक real_cmd, अचिन्हित पूर्णांक cmd,
			  bool *always_copy)
अणु
	अचिन्हित पूर्णांक n = _IOC_SIZE(real_cmd);
	पूर्णांक err = 0;

	अगर (!(_IOC_सूची(cmd) & _IOC_WRITE)) अणु
		/* पढ़ो-only ioctl */
		स_रखो(parg, 0, n);
		वापस 0;
	पूर्ण

	/*
	 * In some हालs, only a few fields are used as input,
	 * i.e. when the app sets "index" and then the driver
	 * fills in the rest of the काष्ठाure क्रम the thing
	 * with that index.  We only need to copy up the first
	 * non-input field.
	 */
	अगर (v4l2_is_known_ioctl(real_cmd)) अणु
		u32 flags = v4l2_ioctls[_IOC_NR(real_cmd)].flags;

		अगर (flags & INFO_FL_CLEAR_MASK)
			n = (flags & INFO_FL_CLEAR_MASK) >> 16;
		*always_copy = flags & INFO_FL_ALWAYS_COPY;
	पूर्ण

	अगर (cmd == real_cmd) अणु
		अगर (copy_from_user(parg, (व्योम __user *)arg, n))
			err = -EFAULT;
	पूर्ण अन्यथा अगर (in_compat_syscall()) अणु
		err = v4l2_compat_get_user(arg, parg, cmd);
	पूर्ण अन्यथा अणु
		चयन (cmd) अणु
#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
		हाल VIDIOC_QUERYBUF_TIME32:
		हाल VIDIOC_QBUF_TIME32:
		हाल VIDIOC_DQBUF_TIME32:
		हाल VIDIOC_PREPARE_BUF_TIME32: अणु
			काष्ठा v4l2_buffer_समय32 vb32;
			काष्ठा v4l2_buffer *vb = parg;

			अगर (copy_from_user(&vb32, arg, माप(vb32)))
				वापस -EFAULT;

			*vb = (काष्ठा v4l2_buffer) अणु
				.index		= vb32.index,
					.type		= vb32.type,
					.bytesused	= vb32.bytesused,
					.flags		= vb32.flags,
					.field		= vb32.field,
					.बारtamp.tv_sec	= vb32.बारtamp.tv_sec,
					.बारtamp.tv_usec	= vb32.बारtamp.tv_usec,
					.समयcode	= vb32.समयcode,
					.sequence	= vb32.sequence,
					.memory		= vb32.memory,
					.m.userptr	= vb32.m.userptr,
					.length		= vb32.length,
					.request_fd	= vb32.request_fd,
			पूर्ण;
			अवरोध;
		पूर्ण
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	/* zero out anything we करोn't copy from userspace */
	अगर (!err && n < _IOC_SIZE(real_cmd))
		स_रखो((u8 *)parg + n, 0, _IOC_SIZE(real_cmd) - n);
	वापस err;
पूर्ण

अटल पूर्णांक video_put_user(व्योम __user *arg, व्योम *parg,
			  अचिन्हित पूर्णांक real_cmd, अचिन्हित पूर्णांक cmd)
अणु
	अगर (!(_IOC_सूची(cmd) & _IOC_READ))
		वापस 0;

	अगर (cmd == real_cmd) अणु
		/*  Copy results पूर्णांकo user buffer  */
		अगर (copy_to_user(arg, parg, _IOC_SIZE(cmd)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण

	अगर (in_compat_syscall())
		वापस v4l2_compat_put_user(arg, parg, cmd);

	चयन (cmd) अणु
#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
	हाल VIDIOC_DQEVENT_TIME32: अणु
		काष्ठा v4l2_event *ev = parg;
		काष्ठा v4l2_event_समय32 ev32;

		स_रखो(&ev32, 0, माप(ev32));

		ev32.type	= ev->type;
		ev32.pending	= ev->pending;
		ev32.sequence	= ev->sequence;
		ev32.बारtamp.tv_sec	= ev->बारtamp.tv_sec;
		ev32.बारtamp.tv_nsec	= ev->बारtamp.tv_nsec;
		ev32.id		= ev->id;

		स_नकल(&ev32.u, &ev->u, माप(ev->u));
		स_नकल(&ev32.reserved, &ev->reserved, माप(ev->reserved));

		अगर (copy_to_user(arg, &ev32, माप(ev32)))
			वापस -EFAULT;
		अवरोध;
	पूर्ण
	हाल VIDIOC_QUERYBUF_TIME32:
	हाल VIDIOC_QBUF_TIME32:
	हाल VIDIOC_DQBUF_TIME32:
	हाल VIDIOC_PREPARE_BUF_TIME32: अणु
		काष्ठा v4l2_buffer *vb = parg;
		काष्ठा v4l2_buffer_समय32 vb32;

		स_रखो(&vb32, 0, माप(vb32));

		vb32.index	= vb->index;
		vb32.type	= vb->type;
		vb32.bytesused	= vb->bytesused;
		vb32.flags	= vb->flags;
		vb32.field	= vb->field;
		vb32.बारtamp.tv_sec	= vb->बारtamp.tv_sec;
		vb32.बारtamp.tv_usec	= vb->बारtamp.tv_usec;
		vb32.समयcode	= vb->समयcode;
		vb32.sequence	= vb->sequence;
		vb32.memory	= vb->memory;
		vb32.m.userptr	= vb->m.userptr;
		vb32.length	= vb->length;
		vb32.request_fd	= vb->request_fd;

		अगर (copy_to_user(arg, &vb32, माप(vb32)))
			वापस -EFAULT;
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	पूर्ण

	वापस 0;
पूर्ण

दीर्घ
video_usercopy(काष्ठा file *file, अचिन्हित पूर्णांक orig_cmd, अचिन्हित दीर्घ arg,
	       v4l2_kioctl func)
अणु
	अक्षर	sbuf[128];
	व्योम    *mbuf = शून्य, *array_buf = शून्य;
	व्योम	*parg = (व्योम *)arg;
	दीर्घ	err  = -EINVAL;
	bool	has_array_args;
	bool	always_copy = false;
	माप_प्रकार  array_size = 0;
	व्योम __user *user_ptr = शून्य;
	व्योम	**kernel_ptr = शून्य;
	अचिन्हित पूर्णांक cmd = video_translate_cmd(orig_cmd);
	स्थिर माप_प्रकार ioc_size = _IOC_SIZE(cmd);

	/*  Copy arguments पूर्णांकo temp kernel buffer  */
	अगर (_IOC_सूची(cmd) != _IOC_NONE) अणु
		अगर (ioc_size <= माप(sbuf)) अणु
			parg = sbuf;
		पूर्ण अन्यथा अणु
			/* too big to allocate from stack */
			mbuf = kदो_स्मृति(ioc_size, GFP_KERNEL);
			अगर (शून्य == mbuf)
				वापस -ENOMEM;
			parg = mbuf;
		पूर्ण

		err = video_get_user((व्योम __user *)arg, parg, cmd,
				     orig_cmd, &always_copy);
		अगर (err)
			जाओ out;
	पूर्ण

	err = check_array_args(cmd, parg, &array_size, &user_ptr, &kernel_ptr);
	अगर (err < 0)
		जाओ out;
	has_array_args = err;

	अगर (has_array_args) अणु
		array_buf = kvदो_स्मृति(array_size, GFP_KERNEL);
		err = -ENOMEM;
		अगर (array_buf == शून्य)
			जाओ out_array_args;
		err = -EFAULT;
		अगर (in_compat_syscall())
			err = v4l2_compat_get_array_args(file, array_buf,
							 user_ptr, array_size,
							 orig_cmd, parg);
		अन्यथा
			err = copy_from_user(array_buf, user_ptr, array_size) ?
								-EFAULT : 0;
		अगर (err)
			जाओ out_array_args;
		*kernel_ptr = array_buf;
	पूर्ण

	/* Handles IOCTL */
	err = func(file, cmd, parg);
	अगर (err == -ENOTTY || err == -ENOIOCTLCMD) अणु
		err = -ENOTTY;
		जाओ out;
	पूर्ण

	अगर (err == 0) अणु
		अगर (cmd == VIDIOC_DQBUF)
			trace_v4l2_dqbuf(video_devdata(file)->minor, parg);
		अन्यथा अगर (cmd == VIDIOC_QBUF)
			trace_v4l2_qbuf(video_devdata(file)->minor, parg);
	पूर्ण

	अगर (has_array_args) अणु
		*kernel_ptr = (व्योम __क्रमce *)user_ptr;
		अगर (in_compat_syscall()) अणु
			पूर्णांक put_err;

			put_err = v4l2_compat_put_array_args(file, user_ptr,
							     array_buf,
							     array_size,
							     orig_cmd, parg);
			अगर (put_err)
				err = put_err;
		पूर्ण अन्यथा अगर (copy_to_user(user_ptr, array_buf, array_size)) अणु
			err = -EFAULT;
		पूर्ण
		जाओ out_array_args;
	पूर्ण
	/*
	 * Some ioctls can वापस an error, but still have valid
	 * results that must be वापसed.
	 */
	अगर (err < 0 && !always_copy)
		जाओ out;

out_array_args:
	अगर (video_put_user((व्योम __user *)arg, parg, cmd, orig_cmd))
		err = -EFAULT;
out:
	kvमुक्त(array_buf);
	kमुक्त(mbuf);
	वापस err;
पूर्ण

दीर्घ video_ioctl2(काष्ठा file *file,
	       अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस video_usercopy(file, cmd, arg, __video_करो_ioctl);
पूर्ण
EXPORT_SYMBOL(video_ioctl2);
