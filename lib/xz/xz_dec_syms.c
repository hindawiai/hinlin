<शैली गुरु>
/*
 * XZ decoder module inक्रमmation
 *
 * Author: Lasse Collin <lasse.collin@tukaani.org>
 *
 * This file has been put पूर्णांकo the खुला करोमुख्य.
 * You can करो whatever you want with this file.
 */

#समावेश <linux/module.h>
#समावेश <linux/xz.h>

EXPORT_SYMBOL(xz_dec_init);
EXPORT_SYMBOL(xz_dec_reset);
EXPORT_SYMBOL(xz_dec_run);
EXPORT_SYMBOL(xz_dec_end);

MODULE_DESCRIPTION("XZ decompressor");
MODULE_VERSION("1.0");
MODULE_AUTHOR("Lasse Collin <lasse.collin@tukaani.org> and Igor Pavlov");

/*
 * This code is in the खुला करोमुख्य, but in Linux it's simplest to just
 * say it's GPL and consider the authors as the copyright holders.
 */
MODULE_LICENSE("GPL");
