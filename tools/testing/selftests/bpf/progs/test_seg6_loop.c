<शैली गुरु>
#समावेश <मानकघोष.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <त्रुटिसं.स>
#समावेश <linux/seg6_local.h>
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

/* Packet parsing state machine helpers. */
#घोषणा cursor_advance(_cursor, _len) \
	(अणु व्योम *_पंचांगp = _cursor; _cursor += _len; _पंचांगp; पूर्ण)

#घोषणा SR6_FLAG_ALERT (1 << 4)

#घोषणा BPF_PACKET_HEADER __attribute__((packed))

काष्ठा ip6_t अणु
	अचिन्हित पूर्णांक ver:4;
	अचिन्हित पूर्णांक priority:8;
	अचिन्हित पूर्णांक flow_label:20;
	अचिन्हित लघु payload_len;
	अचिन्हित अक्षर next_header;
	अचिन्हित अक्षर hop_limit;
	अचिन्हित दीर्घ दीर्घ src_hi;
	अचिन्हित दीर्घ दीर्घ src_lo;
	अचिन्हित दीर्घ दीर्घ dst_hi;
	अचिन्हित दीर्घ दीर्घ dst_lo;
पूर्ण BPF_PACKET_HEADER;

काष्ठा ip6_addr_t अणु
	अचिन्हित दीर्घ दीर्घ hi;
	अचिन्हित दीर्घ दीर्घ lo;
पूर्ण BPF_PACKET_HEADER;

काष्ठा ip6_srh_t अणु
	अचिन्हित अक्षर nexthdr;
	अचिन्हित अक्षर hdrlen;
	अचिन्हित अक्षर type;
	अचिन्हित अक्षर segments_left;
	अचिन्हित अक्षर first_segment;
	अचिन्हित अक्षर flags;
	अचिन्हित लघु tag;

	काष्ठा ip6_addr_t segments[0];
पूर्ण BPF_PACKET_HEADER;

काष्ठा sr6_tlv_t अणु
	अचिन्हित अक्षर type;
	अचिन्हित अक्षर len;
	अचिन्हित अक्षर value[0];
पूर्ण BPF_PACKET_HEADER;

अटल __always_अंतरभूत काष्ठा ip6_srh_t *get_srh(काष्ठा __sk_buff *skb)
अणु
	व्योम *cursor, *data_end;
	काष्ठा ip6_srh_t *srh;
	काष्ठा ip6_t *ip;
	uपूर्णांक8_t *ipver;

	data_end = (व्योम *)(दीर्घ)skb->data_end;
	cursor = (व्योम *)(दीर्घ)skb->data;
	ipver = (uपूर्णांक8_t *)cursor;

	अगर ((व्योम *)ipver + माप(*ipver) > data_end)
		वापस शून्य;

	अगर ((*ipver >> 4) != 6)
		वापस शून्य;

	ip = cursor_advance(cursor, माप(*ip));
	अगर ((व्योम *)ip + माप(*ip) > data_end)
		वापस शून्य;

	अगर (ip->next_header != 43)
		वापस शून्य;

	srh = cursor_advance(cursor, माप(*srh));
	अगर ((व्योम *)srh + माप(*srh) > data_end)
		वापस शून्य;

	अगर (srh->type != 4)
		वापस शून्य;

	वापस srh;
पूर्ण

अटल __always_अंतरभूत पूर्णांक update_tlv_pad(काष्ठा __sk_buff *skb,
					  uपूर्णांक32_t new_pad, uपूर्णांक32_t old_pad,
					  uपूर्णांक32_t pad_off)
अणु
	पूर्णांक err;

	अगर (new_pad != old_pad) अणु
		err = bpf_lwt_seg6_adjust_srh(skb, pad_off,
					  (पूर्णांक) new_pad - (पूर्णांक) old_pad);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (new_pad > 0) अणु
		अक्षर pad_tlv_buf[16] = अणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0पूर्ण;
		काष्ठा sr6_tlv_t *pad_tlv = (काष्ठा sr6_tlv_t *) pad_tlv_buf;

		pad_tlv->type = SR6_TLV_PADDING;
		pad_tlv->len = new_pad - 2;

		err = bpf_lwt_seg6_store_bytes(skb, pad_off,
					       (व्योम *)pad_tlv_buf, new_pad);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल __always_अंतरभूत पूर्णांक is_valid_tlv_boundary(काष्ठा __sk_buff *skb,
						 काष्ठा ip6_srh_t *srh,
						 uपूर्णांक32_t *tlv_off,
						 uपूर्णांक32_t *pad_size,
						 uपूर्णांक32_t *pad_off)
अणु
	uपूर्णांक32_t srh_off, cur_off;
	पूर्णांक offset_valid = 0;
	पूर्णांक err;

	srh_off = (अक्षर *)srh - (अक्षर *)(दीर्घ)skb->data;
	// cur_off = end of segments, start of possible TLVs
	cur_off = srh_off + माप(*srh) +
		माप(काष्ठा ip6_addr_t) * (srh->first_segment + 1);

	*pad_off = 0;

	// we can only go as far as ~10 TLVs due to the BPF max stack size
	// workaround: define induction variable "i" as "long" instead
	// of "int" to prevent alu32 sub-रेजिस्टर spilling.
	#आशय clang loop unroll(disable)
	क्रम (दीर्घ i = 0; i < 100; i++) अणु
		काष्ठा sr6_tlv_t tlv;

		अगर (cur_off == *tlv_off)
			offset_valid = 1;

		अगर (cur_off >= srh_off + ((srh->hdrlen + 1) << 3))
			अवरोध;

		err = bpf_skb_load_bytes(skb, cur_off, &tlv, माप(tlv));
		अगर (err)
			वापस err;

		अगर (tlv.type == SR6_TLV_PADDING) अणु
			*pad_size = tlv.len + माप(tlv);
			*pad_off = cur_off;

			अगर (*tlv_off == srh_off) अणु
				*tlv_off = cur_off;
				offset_valid = 1;
			पूर्ण
			अवरोध;

		पूर्ण अन्यथा अगर (tlv.type == SR6_TLV_HMAC) अणु
			अवरोध;
		पूर्ण

		cur_off += माप(tlv) + tlv.len;
	पूर्ण // we reached the padding or HMAC TLVs, or the end of the SRH

	अगर (*pad_off == 0)
		*pad_off = cur_off;

	अगर (*tlv_off == -1)
		*tlv_off = cur_off;
	अन्यथा अगर (!offset_valid)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल __always_अंतरभूत पूर्णांक add_tlv(काष्ठा __sk_buff *skb,
				   काष्ठा ip6_srh_t *srh, uपूर्णांक32_t tlv_off,
				   काष्ठा sr6_tlv_t *itlv, uपूर्णांक8_t tlv_size)
अणु
	uपूर्णांक32_t srh_off = (अक्षर *)srh - (अक्षर *)(दीर्घ)skb->data;
	uपूर्णांक8_t len_reमुख्यing, new_pad;
	uपूर्णांक32_t pad_off = 0;
	uपूर्णांक32_t pad_size = 0;
	uपूर्णांक32_t partial_srh_len;
	पूर्णांक err;

	अगर (tlv_off != -1)
		tlv_off += srh_off;

	अगर (itlv->type == SR6_TLV_PADDING || itlv->type == SR6_TLV_HMAC)
		वापस -EINVAL;

	err = is_valid_tlv_boundary(skb, srh, &tlv_off, &pad_size, &pad_off);
	अगर (err)
		वापस err;

	err = bpf_lwt_seg6_adjust_srh(skb, tlv_off, माप(*itlv) + itlv->len);
	अगर (err)
		वापस err;

	err = bpf_lwt_seg6_store_bytes(skb, tlv_off, (व्योम *)itlv, tlv_size);
	अगर (err)
		वापस err;

	// the following can't be moved inside update_tlv_pad because the
	// bpf verअगरier has some issues with it
	pad_off += माप(*itlv) + itlv->len;
	partial_srh_len = pad_off - srh_off;
	len_reमुख्यing = partial_srh_len % 8;
	new_pad = 8 - len_reमुख्यing;

	अगर (new_pad == 1) // cannot pad क्रम 1 byte only
		new_pad = 9;
	अन्यथा अगर (new_pad == 8)
		new_pad = 0;

	वापस update_tlv_pad(skb, new_pad, pad_size, pad_off);
पूर्ण

// Add an Egress TLV fc00::4, add the flag A,
// and apply End.X action to fc42::1
SEC("lwt_seg6local")
पूर्णांक __add_egr_x(काष्ठा __sk_buff *skb)
अणु
	अचिन्हित दीर्घ दीर्घ hi = 0xfc42000000000000;
	अचिन्हित दीर्घ दीर्घ lo = 0x1;
	काष्ठा ip6_srh_t *srh = get_srh(skb);
	uपूर्णांक8_t new_flags = SR6_FLAG_ALERT;
	काष्ठा ip6_addr_t addr;
	पूर्णांक err, offset;

	अगर (srh == शून्य)
		वापस BPF_DROP;

	uपूर्णांक8_t tlv[20] = अणु2, 18, 0, 0, 0xfd, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
			   0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4पूर्ण;

	err = add_tlv(skb, srh, (srh->hdrlen+1) << 3,
		      (काष्ठा sr6_tlv_t *)&tlv, 20);
	अगर (err)
		वापस BPF_DROP;

	offset = माप(काष्ठा ip6_t) + दुरत्व(काष्ठा ip6_srh_t, flags);
	err = bpf_lwt_seg6_store_bytes(skb, offset,
				       (व्योम *)&new_flags, माप(new_flags));
	अगर (err)
		वापस BPF_DROP;

	addr.lo = bpf_cpu_to_be64(lo);
	addr.hi = bpf_cpu_to_be64(hi);
	err = bpf_lwt_seg6_action(skb, SEG6_LOCAL_ACTION_END_X,
				  (व्योम *)&addr, माप(addr));
	अगर (err)
		वापस BPF_DROP;
	वापस BPF_REसूचीECT;
पूर्ण
अक्षर __license[] SEC("license") = "GPL";
