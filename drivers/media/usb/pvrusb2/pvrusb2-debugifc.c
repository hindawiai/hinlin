<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2005 Mike Isely <isely@pobox.com>
 */

#समावेश <linux/माला.स>
#समावेश "pvrusb2-debugifc.h"
#समावेश "pvrusb2-hdw.h"
#समावेश "pvrusb2-debug.h"

काष्ठा debugअगरc_mask_item अणु
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ msk;
पूर्ण;


अटल अचिन्हित पूर्णांक debugअगरc_count_whitespace(स्थिर अक्षर *buf,
					      अचिन्हित पूर्णांक count)
अणु
	अचिन्हित पूर्णांक scnt;
	अक्षर ch;

	क्रम (scnt = 0; scnt < count; scnt++) अणु
		ch = buf[scnt];
		अगर (ch == ' ') जारी;
		अगर (ch == '\t') जारी;
		अगर (ch == '\n') जारी;
		अवरोध;
	पूर्ण
	वापस scnt;
पूर्ण


अटल अचिन्हित पूर्णांक debugअगरc_count_nonwhitespace(स्थिर अक्षर *buf,
						 अचिन्हित पूर्णांक count)
अणु
	अचिन्हित पूर्णांक scnt;
	अक्षर ch;

	क्रम (scnt = 0; scnt < count; scnt++) अणु
		ch = buf[scnt];
		अगर (ch == ' ') अवरोध;
		अगर (ch == '\t') अवरोध;
		अगर (ch == '\n') अवरोध;
	पूर्ण
	वापस scnt;
पूर्ण


अटल अचिन्हित पूर्णांक debugअगरc_isolate_word(स्थिर अक्षर *buf,अचिन्हित पूर्णांक count,
					  स्थिर अक्षर **wstrPtr,
					  अचिन्हित पूर्णांक *wlenPtr)
अणु
	स्थिर अक्षर *wptr;
	अचिन्हित पूर्णांक consume_cnt = 0;
	अचिन्हित पूर्णांक wlen;
	अचिन्हित पूर्णांक scnt;

	wptr = शून्य;
	wlen = 0;
	scnt = debugअगरc_count_whitespace(buf,count);
	consume_cnt += scnt; count -= scnt; buf += scnt;
	अगर (!count) जाओ करोne;

	scnt = debugअगरc_count_nonwhitespace(buf,count);
	अगर (!scnt) जाओ करोne;
	wptr = buf;
	wlen = scnt;
	consume_cnt += scnt; count -= scnt; buf += scnt;

 करोne:
	*wstrPtr = wptr;
	*wlenPtr = wlen;
	वापस consume_cnt;
पूर्ण


अटल पूर्णांक debugअगरc_parse_अचिन्हित_number(स्थिर अक्षर *buf,अचिन्हित पूर्णांक count,
					  u32 *num_ptr)
अणु
	u32 result = 0;
	पूर्णांक radix = 10;
	अगर ((count >= 2) && (buf[0] == '0') &&
	    ((buf[1] == 'x') || (buf[1] == 'X'))) अणु
		radix = 16;
		count -= 2;
		buf += 2;
	पूर्ण अन्यथा अगर ((count >= 1) && (buf[0] == '0')) अणु
		radix = 8;
	पूर्ण

	जबतक (count--) अणु
		पूर्णांक val = hex_to_bin(*buf++);
		अगर (val < 0 || val >= radix)
			वापस -EINVAL;
		result *= radix;
		result += val;
	पूर्ण
	*num_ptr = result;
	वापस 0;
पूर्ण


अटल पूर्णांक debugअगरc_match_keyword(स्थिर अक्षर *buf,अचिन्हित पूर्णांक count,
				  स्थिर अक्षर *keyword)
अणु
	अचिन्हित पूर्णांक kl;
	अगर (!keyword) वापस 0;
	kl = म_माप(keyword);
	अगर (kl != count) वापस 0;
	वापस !स_भेद(buf,keyword,kl);
पूर्ण


पूर्णांक pvr2_debugअगरc_prपूर्णांक_info(काष्ठा pvr2_hdw *hdw,अक्षर *buf,अचिन्हित पूर्णांक acnt)
अणु
	पूर्णांक bcnt = 0;
	पूर्णांक ccnt;
	ccnt = scnम_लिखो(buf, acnt, "Driver hardware description: %s\n",
			 pvr2_hdw_get_desc(hdw));
	bcnt += ccnt; acnt -= ccnt; buf += ccnt;
	ccnt = scnम_लिखो(buf,acnt,"Driver state info:\n");
	bcnt += ccnt; acnt -= ccnt; buf += ccnt;
	ccnt = pvr2_hdw_state_report(hdw,buf,acnt);
	bcnt += ccnt; acnt -= ccnt; buf += ccnt;

	वापस bcnt;
पूर्ण


पूर्णांक pvr2_debugअगरc_prपूर्णांक_status(काष्ठा pvr2_hdw *hdw,
			       अक्षर *buf,अचिन्हित पूर्णांक acnt)
अणु
	पूर्णांक bcnt = 0;
	पूर्णांक ccnt;
	पूर्णांक ret;
	u32 gpio_dir,gpio_in,gpio_out;
	काष्ठा pvr2_stream_stats stats;
	काष्ठा pvr2_stream *sp;

	ret = pvr2_hdw_is_hsm(hdw);
	ccnt = scnम_लिखो(buf,acnt,"USB link speed: %s\n",
			 (ret < 0 ? "FAIL" : (ret ? "high" : "full")));
	bcnt += ccnt; acnt -= ccnt; buf += ccnt;

	gpio_dir = 0; gpio_in = 0; gpio_out = 0;
	pvr2_hdw_gpio_get_dir(hdw,&gpio_dir);
	pvr2_hdw_gpio_get_out(hdw,&gpio_out);
	pvr2_hdw_gpio_get_in(hdw,&gpio_in);
	ccnt = scnम_लिखो(buf,acnt,"GPIO state: dir=0x%x in=0x%x out=0x%x\n",
			 gpio_dir,gpio_in,gpio_out);
	bcnt += ccnt; acnt -= ccnt; buf += ccnt;

	ccnt = scnम_लिखो(buf,acnt,"Streaming is %s\n",
			 pvr2_hdw_get_streaming(hdw) ? "on" : "off");
	bcnt += ccnt; acnt -= ccnt; buf += ccnt;


	sp = pvr2_hdw_get_video_stream(hdw);
	अगर (sp) अणु
		pvr2_stream_get_stats(sp, &stats, 0);
		ccnt = scnम_लिखो(
			buf,acnt,
			"Bytes streamed=%u URBs: queued=%u idle=%u ready=%u processed=%u failed=%u\n",
			stats.bytes_processed,
			stats.buffers_in_queue,
			stats.buffers_in_idle,
			stats.buffers_in_पढ़ोy,
			stats.buffers_processed,
			stats.buffers_failed);
		bcnt += ccnt; acnt -= ccnt; buf += ccnt;
	पूर्ण

	वापस bcnt;
पूर्ण


अटल पूर्णांक pvr2_debugअगरc_करो1cmd(काष्ठा pvr2_hdw *hdw,स्थिर अक्षर *buf,
				अचिन्हित पूर्णांक count)
अणु
	स्थिर अक्षर *wptr;
	अचिन्हित पूर्णांक wlen;
	अचिन्हित पूर्णांक scnt;

	scnt = debugअगरc_isolate_word(buf,count,&wptr,&wlen);
	अगर (!scnt) वापस 0;
	count -= scnt; buf += scnt;
	अगर (!wptr) वापस 0;

	pvr2_trace(PVR2_TRACE_DEBUGIFC,"debugifc cmd: \"%.*s\"",wlen,wptr);
	अगर (debugअगरc_match_keyword(wptr,wlen,"reset")) अणु
		scnt = debugअगरc_isolate_word(buf,count,&wptr,&wlen);
		अगर (!scnt) वापस -EINVAL;
		count -= scnt; buf += scnt;
		अगर (!wptr) वापस -EINVAL;
		अगर (debugअगरc_match_keyword(wptr,wlen,"cpu")) अणु
			pvr2_hdw_cpureset_निश्चित(hdw,!0);
			pvr2_hdw_cpureset_निश्चित(hdw,0);
			वापस 0;
		पूर्ण अन्यथा अगर (debugअगरc_match_keyword(wptr,wlen,"bus")) अणु
			pvr2_hdw_device_reset(hdw);
		पूर्ण अन्यथा अगर (debugअगरc_match_keyword(wptr,wlen,"soft")) अणु
			वापस pvr2_hdw_cmd_घातerup(hdw);
		पूर्ण अन्यथा अगर (debugअगरc_match_keyword(wptr,wlen,"deep")) अणु
			वापस pvr2_hdw_cmd_deep_reset(hdw);
		पूर्ण अन्यथा अगर (debugअगरc_match_keyword(wptr,wlen,"firmware")) अणु
			वापस pvr2_upload_firmware2(hdw);
		पूर्ण अन्यथा अगर (debugअगरc_match_keyword(wptr,wlen,"decoder")) अणु
			वापस pvr2_hdw_cmd_decoder_reset(hdw);
		पूर्ण अन्यथा अगर (debugअगरc_match_keyword(wptr,wlen,"worker")) अणु
			वापस pvr2_hdw_untrip(hdw);
		पूर्ण अन्यथा अगर (debugअगरc_match_keyword(wptr,wlen,"usbstats")) अणु
			pvr2_stream_get_stats(pvr2_hdw_get_video_stream(hdw),
					      शून्य, !0);
			वापस 0;
		पूर्ण
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (debugअगरc_match_keyword(wptr,wlen,"cpufw")) अणु
		scnt = debugअगरc_isolate_word(buf,count,&wptr,&wlen);
		अगर (!scnt) वापस -EINVAL;
		count -= scnt; buf += scnt;
		अगर (!wptr) वापस -EINVAL;
		अगर (debugअगरc_match_keyword(wptr,wlen,"fetch")) अणु
			scnt = debugअगरc_isolate_word(buf,count,&wptr,&wlen);
			अगर (scnt && wptr) अणु
				count -= scnt; buf += scnt;
				अगर (debugअगरc_match_keyword(wptr, wlen,
							   "prom")) अणु
					pvr2_hdw_cpufw_set_enabled(hdw, 2, !0);
				पूर्ण अन्यथा अगर (debugअगरc_match_keyword(wptr, wlen,
								  "ram8k")) अणु
					pvr2_hdw_cpufw_set_enabled(hdw, 0, !0);
				पूर्ण अन्यथा अगर (debugअगरc_match_keyword(wptr, wlen,
								  "ram16k")) अणु
					pvr2_hdw_cpufw_set_enabled(hdw, 1, !0);
				पूर्ण अन्यथा अणु
					वापस -EINVAL;
				पूर्ण
			पूर्ण
			pvr2_hdw_cpufw_set_enabled(hdw,0,!0);
			वापस 0;
		पूर्ण अन्यथा अगर (debugअगरc_match_keyword(wptr,wlen,"done")) अणु
			pvr2_hdw_cpufw_set_enabled(hdw,0,0);
			वापस 0;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (debugअगरc_match_keyword(wptr,wlen,"gpio")) अणु
		पूर्णांक dir_fl = 0;
		पूर्णांक ret;
		u32 msk,val;
		scnt = debugअगरc_isolate_word(buf,count,&wptr,&wlen);
		अगर (!scnt) वापस -EINVAL;
		count -= scnt; buf += scnt;
		अगर (!wptr) वापस -EINVAL;
		अगर (debugअगरc_match_keyword(wptr,wlen,"dir")) अणु
			dir_fl = !0;
		पूर्ण अन्यथा अगर (!debugअगरc_match_keyword(wptr,wlen,"out")) अणु
			वापस -EINVAL;
		पूर्ण
		scnt = debugअगरc_isolate_word(buf,count,&wptr,&wlen);
		अगर (!scnt) वापस -EINVAL;
		count -= scnt; buf += scnt;
		अगर (!wptr) वापस -EINVAL;
		ret = debugअगरc_parse_अचिन्हित_number(wptr,wlen,&msk);
		अगर (ret) वापस ret;
		scnt = debugअगरc_isolate_word(buf,count,&wptr,&wlen);
		अगर (wptr) अणु
			ret = debugअगरc_parse_अचिन्हित_number(wptr,wlen,&val);
			अगर (ret) वापस ret;
		पूर्ण अन्यथा अणु
			val = msk;
			msk = 0xffffffff;
		पूर्ण
		अगर (dir_fl) अणु
			ret = pvr2_hdw_gpio_chg_dir(hdw,msk,val);
		पूर्ण अन्यथा अणु
			ret = pvr2_hdw_gpio_chg_out(hdw,msk,val);
		पूर्ण
		वापस ret;
	पूर्ण
	pvr2_trace(PVR2_TRACE_DEBUGIFC,
		   "debugifc failed to recognize cmd: \"%.*s\"",wlen,wptr);
	वापस -EINVAL;
पूर्ण


पूर्णांक pvr2_debugअगरc_करोcmd(काष्ठा pvr2_hdw *hdw,स्थिर अक्षर *buf,
			अचिन्हित पूर्णांक count)
अणु
	अचिन्हित पूर्णांक bcnt = 0;
	पूर्णांक ret;

	जबतक (count) अणु
		क्रम (bcnt = 0; bcnt < count; bcnt++) अणु
			अगर (buf[bcnt] == '\n') अवरोध;
		पूर्ण

		ret = pvr2_debugअगरc_करो1cmd(hdw,buf,bcnt);
		अगर (ret < 0) वापस ret;
		अगर (bcnt < count) bcnt++;
		buf += bcnt;
		count -= bcnt;
	पूर्ण

	वापस 0;
पूर्ण
