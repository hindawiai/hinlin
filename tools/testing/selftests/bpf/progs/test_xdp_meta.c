<शैली गुरु>
#समावेश <linux/bpf.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/pkt_cls.h>

#समावेश <bpf/bpf_helpers.h>

#घोषणा __round_mask(x, y) ((__typeof__(x))((y) - 1))
#घोषणा round_up(x, y) ((((x) - 1) | __round_mask(x, y)) + 1)
#घोषणा ctx_ptr(ctx, mem) (व्योम *)(अचिन्हित दीर्घ)ctx->mem

SEC("t")
पूर्णांक ing_cls(काष्ठा __sk_buff *ctx)
अणु
	__u8 *data, *data_meta, *data_end;
	__u32 dअगरf = 0;

	data_meta = ctx_ptr(ctx, data_meta);
	data_end  = ctx_ptr(ctx, data_end);
	data      = ctx_ptr(ctx, data);

	अगर (data + ETH_ALEN > data_end ||
	    data_meta + round_up(ETH_ALEN, 4) > data)
		वापस TC_ACT_SHOT;

	dअगरf |= ((__u32 *)data_meta)[0] ^ ((__u32 *)data)[0];
	dअगरf |= ((__u16 *)data_meta)[2] ^ ((__u16 *)data)[2];

	वापस dअगरf ? TC_ACT_SHOT : TC_ACT_OK;
पूर्ण

SEC("x")
पूर्णांक ing_xdp(काष्ठा xdp_md *ctx)
अणु
	__u8 *data, *data_meta, *data_end;
	पूर्णांक ret;

	ret = bpf_xdp_adjust_meta(ctx, -round_up(ETH_ALEN, 4));
	अगर (ret < 0)
		वापस XDP_DROP;

	data_meta = ctx_ptr(ctx, data_meta);
	data_end  = ctx_ptr(ctx, data_end);
	data      = ctx_ptr(ctx, data);

	अगर (data + ETH_ALEN > data_end ||
	    data_meta + round_up(ETH_ALEN, 4) > data)
		वापस XDP_DROP;

	__builtin_स_नकल(data_meta, data, ETH_ALEN);
	वापस XDP_PASS;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
