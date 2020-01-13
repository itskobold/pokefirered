#include "global.h"
#include "librfu.h"
#include "link_rfu.h"

struct UnkRfuStruct_1 gUnknown_3005E10;

void sub_80FD4E4(void);
void sub_80FDC28(u32 a0);
void sub_80FDC98(u16 reqCommandId, u16 reqResult);
void sub_80FE394(u16 reqCommandId);
void sub_80FE418(void);
void sub_80FE63C(void);
void sub_80FE6F0(void);
void sub_80FE74C(void);
u8 sub_80FE778(void);
void sub_80FE7F0(u8 a0, u8 a1);
void sub_80FE818(u8 bmDisconnectSlot);
void sub_80FE83C(u8 a0);
void sub_80FE918(void);
void sub_80FEAF4(void);
void sub_80FEB14(void);

u32 sub_80FD3A4(void)
{
    u32 id = rfu_REQBN_softReset_and_checkID();
    if (id == 0x8001)
        gUnknown_3005E10.unk_08 = 1;
    if (gUnknown_3005E10.unk_04 != 0x17 && gUnknown_3005E10.unk_04 != 0x01)
    {
        gUnknown_3005E10.unk_05 = 0;
        gUnknown_3005E10.unk_04 = 0;
    }
    gUnknown_3005E10.unk_07 = 0;
    gUnknown_3005E10.unk_0d = 0;
    gUnknown_3005E10.unk_01 = 0;
    gUnknown_3005E10.unk_00 = 0;
    gUnknown_3005E10.unk_06 = -1;
    sub_80FEAF4();
    return id;
}

void rfu_REQ_sendData_wrapper(u8 clockChangeFlag)
{
    if (gRfuLinkStatus->parentChild == MODE_CHILD)
    {
        if (gUnknown_3005E10.unk_02 == 1)
            clockChangeFlag = 1;
        else
            clockChangeFlag = 0;
    }
    else
        gUnknown_3005E10.unk_03 = 0;
    rfu_REQ_sendData(clockChangeFlag);
}

s32 sub_80FD430(void (*func1)(u8, u8), void (*func2)(u16))
{
    if (func1 == NULL)
    {
        return 4;
    }
    CpuFill16(0, &gUnknown_3005E10, offsetof(struct UnkRfuStruct_1, filler_48));
    gUnknown_3005E10.unk_06 = -1;
    gUnknown_3005E10.unk_40 = func1;
    gUnknown_3005E10.unk_44 = func2;
    rfu_setMSCCallback(sub_80FE394);
    rfu_setREQCallback(sub_80FDC98);
    return 0;
}

void sub_80FD484(void)
{
    CpuFill16(0, &gUnknown_3005E10, offsetof(struct UnkRfuStruct_1, unk_40));
    gUnknown_3005E10.unk_06 = -1;
}

void sub_80FD4B0(const struct UnkLinkRfuStruct_02022B2C *unk0)
{
    sub_80FD4E4();
    gUnknown_3005E10.unk_04 = 1;
    gUnknown_3005E10.unk_05 = 2;
    gUnknown_3005E10.unk_3c = unk0;
    gUnknown_3005E10.unk_09 = unk0->unk_11;
    gUnknown_3005E10.unk_32 = unk0->unk_12;
    gUnknown_3005E10.unk_18 = unk0->unk_14;
    if (unk0->unk_10)
    {
        gUnknown_3005E10.unk_0b = 1;
    }
}

void sub_80FD4E4(void)
{
    u8 i;

    gUnknown_3005E10.unk_05 = 0;
    gUnknown_3005E10.unk_04 = 0;
    gUnknown_3005E10.unk_06 = -1;
    gUnknown_3005E10.unk_07 = 0;
    gUnknown_3005E10.unk_10 = 0;
    gUnknown_3005E10.unk_0c = 0;
    gUnknown_3005E10.unk_24 = 0;
    gUnknown_3005E10.unk_30 = 0;
    for (i = 0; i < RFU_CHILD_MAX; i++)
    {
        gUnknown_3005E10.unk_28[i] = 0;
        gUnknown_3005E10.unk_34[i] = 0;
    }
}

void sub_80FD52C(void)
{
    gUnknown_3005E10.unk_04 = 0x15;
}

u8 sub_80FD538(u8 r5, u16 r7, u16 r8, const u16 *r6)
{
    u8 i;
    const u16 *buffer;

    if (gUnknown_3005E10.unk_04 != 0 && (gUnknown_3005E10.unk_04 != 0x08 || r5 != 1))
    {
        gUnknown_3005E10.unk_14 = 1;
        sub_80FE7F0(0xf3, 0x01);
        return 1;
    }
    if (!rfu_getMasterSlave())
    {
        gUnknown_3005E10.unk_14 = 2;
        sub_80FE7F0(0xf3, 0x01);
        return 2;
    }
    for (i = 0, buffer = r6; i < 16; i++)
    {
        if (*buffer++ == 0xFFFF)
        {
            break;
        }
    }
    if (i == 16)
    {
        gUnknown_3005E10.unk_14 = 4;
        sub_80FE7F0(0xf3, 0x01);
        return 4;
    }
    if (r5 > 1)
    {
        gUnknown_3005E10.unk_07 = 1;
        r5 = 1;
        r7 = 0;
    }
    else
    {
        gUnknown_3005E10.unk_07 = 0;
    }
    if (r5 != 0)
    {
        gUnknown_3005E10.unk_04 = 5;
    }
    else
    {
        gUnknown_3005E10.unk_04 = 9;
        if (gUnknown_3005E10.unk_0b)
        {
            gUnknown_3005E10.unk_0b = 2;
        }
    }
    gUnknown_3005E10.unk_06 = r5;
    gUnknown_3005E10.unk_1a = r7;
    gUnknown_3005E10.unk_26 = r8;
    gUnknown_3005E10.unk_20 = r6;
    return 0;
}

u8 sub_80FD610(u16 parentId, u16 unk_1a)
{
    u8 i;

    if (gUnknown_3005E10.unk_04 != 0 && (gUnknown_3005E10.unk_04 < 9 || gUnknown_3005E10.unk_04 > 11))
    {
        gUnknown_3005E10.unk_14 = 1;
        sub_80FE7F0(0xF3, 0x01);
        return 1;
    }
    if (!rfu_getMasterSlave())
    {
        gUnknown_3005E10.unk_14 = 2;
        sub_80FE7F0(0xF3, 0x01);
        return 2;
    }
    for (i = 0; i < gRfuLinkStatus->findParentCount; i++)
    {
        if (gRfuLinkStatus->partner[i].id == parentId)
        {
            break;
        }
    }
    if (gRfuLinkStatus->findParentCount == 0 || i == gRfuLinkStatus->findParentCount)
    {
        gUnknown_3005E10.unk_14 = 3;
        sub_80FE7F0(0xF3, 0x01);
        return 3;
    }
    if (gUnknown_3005E10.unk_04 == 0 || gUnknown_3005E10.unk_04 == 9)
    {
        gUnknown_3005E10.unk_04 = 12;
        gUnknown_3005E10.unk_05 = 13;
    }
    else
    {
        gUnknown_3005E10.unk_04 = 11;
        gUnknown_3005E10.unk_05 = 12;
    }
    gUnknown_3005E10.unk_1e = parentId;
    gUnknown_3005E10.unk_1a = unk_1a;
    if (gUnknown_3005E10.unk_07 != 0)
    {
        gUnknown_3005E10.unk_07 = 7;
    }
    return 0;
}

void sub_80FD6F4(u8 lossSlot)
{
    u8 i;

    if (lossSlot & gUnknown_3005E10.unk_30)
    {
        gUnknown_3005E10.unk_30 &= ~lossSlot;
        for (i = 0; i < RFU_CHILD_MAX; i++)
        {
            if ((lossSlot >> i) & 1)
            {
                gUnknown_3005E10.unk_34[i] = 0;
            }
        }
        i = gRfuLinkStatus->linkLossSlotFlag & lossSlot;
        if (i)
        {
            sub_80FE818(i);
        }
        gUnknown_3005E10.unk_14 = i;
        sub_80FE7F0(0x33, i);
    }
}

void sub_80FD760(bool8 a0)
{
    u8 r2;

    r2 = 0;
    gUnknown_3005E10.unk_07 = 0;
    if (a0)
    {
        sub_80FD4E4();
        gUnknown_3005E10.unk_04 = 23;
    }
    else
    {
        switch (gUnknown_3005E10.unk_04)
        {
        case 5:
            gUnknown_3005E10.unk_04 = 8;
            gUnknown_3005E10.unk_05 = 0;
            r2 = 0x13;
            break;
        case 6:
            gUnknown_3005E10.unk_04 = 7;
            gUnknown_3005E10.unk_05 = 8;
            break;
        case 7:
            gUnknown_3005E10.unk_04 = 7;
            gUnknown_3005E10.unk_05 = 8;
            break;
        case 8:
            break;
        case 9:
            gUnknown_3005E10.unk_05 = 0;
            gUnknown_3005E10.unk_04 = 0;
            r2 = 0x21;
            break;
        case 10:
            gUnknown_3005E10.unk_04 = 11;
            gUnknown_3005E10.unk_05 = 0;
            break;
        case 11:
            gUnknown_3005E10.unk_04 = 11;
            gUnknown_3005E10.unk_05 = 0;
            break;
        case 12:
            gUnknown_3005E10.unk_05 = 0;
            gUnknown_3005E10.unk_04 = 0;
            r2 = 0x23;
            break;
        case 13:
            gUnknown_3005E10.unk_04 = 14;
            break;
        case 14:
            gUnknown_3005E10.unk_04 = 14;
            break;
        case 15:
            break;
        case 16:
            gUnknown_3005E10.unk_04 = gUnknown_3005E10.unk_11;
            gUnknown_3005E10.unk_05 = gUnknown_3005E10.unk_12;
            sub_80FE818(gRfuLinkStatus->linkLossSlotFlag);
            gUnknown_3005E10.unk_14 = gRfuLinkStatus->linkLossSlotFlag;
            sub_80FE7F0(0x33, 0x01);
            return;
        case 17:
            gUnknown_3005E10.unk_04 = 18;
            break;
        case 18:
            gUnknown_3005E10.unk_04 = 18;
            break;
        default:
            gUnknown_3005E10.unk_05 = 0;
            gUnknown_3005E10.unk_04 = 0;
            r2 = 0x43;
            break;
        }
        if (gUnknown_3005E10.unk_04 == 0)
        {
            sub_80FE7F0(r2, 0);
        }
    }
}

bool8 sub_80FD850(u16 reqCommandId)
{
    bool8 retVal;
    u8 i;
    u8 bmLinkLossSlot;
    u8 linkLossReason;
    u8 parentBmLinkRecoverySlot;
    u8 flags;

    retVal = FALSE;
    rfu_REQBN_watchLink(reqCommandId, &bmLinkLossSlot, &linkLossReason, &parentBmLinkRecoverySlot);
    if (bmLinkLossSlot)
    {
        gUnknown_3005E10.unk_14 = bmLinkLossSlot;
        gUnknown_3005E10.unk_16 = linkLossReason;
        if (gUnknown_3005E10.unk_09)
        {
            gUnknown_3005E10.unk_0a = 1;
            if (gUnknown_3005E10.unk_06 == 0 && linkLossReason == REASON_DISCONNECTED)
            {
                gUnknown_3005E10.unk_0a = 4;
            }
            if (gUnknown_3005E10.unk_0a == 1)
            {
                for (i = 0; i < 4; i++)
                {
                    if ((bmLinkLossSlot >> i) & 1)
                    {
                        gUnknown_3005E10.unk_30 |= (1 << i);
                        gUnknown_3005E10.unk_34[i] = gUnknown_3005E10.unk_32;
                    }
                }
                sub_80FE7F0(0x31, 0x01);
            }
            else
            {
                gUnknown_3005E10.unk_0a = 0;
                sub_80FE818(bmLinkLossSlot);
                retVal = TRUE;
                sub_80FE7F0(0x33, 0x01);
            }
        }
        else
        {
            sub_80FE818(bmLinkLossSlot);
            retVal = TRUE;
            sub_80FE7F0(0x30, 0x02);
        }
        sub_80FEAF4();
    }
    if (gRfuLinkStatus->parentChild == 1)
    {
        if (parentBmLinkRecoverySlot)
        {
            for (i = 0; i < 4; i++)
            {
                if ((gUnknown_3005E10.unk_30 >> i) & 1 && (parentBmLinkRecoverySlot >> i) & 1)
                {
                    gUnknown_3005E10.unk_34[i] = 0;
                }
            }
            gUnknown_3005E10.unk_30 &= ~parentBmLinkRecoverySlot;
            gUnknown_3005E10.unk_14 = parentBmLinkRecoverySlot;
            sub_80FE7F0(0x32, 0x01);
        }
        if (gUnknown_3005E10.unk_30)
        {
            flags = 0;
            for (i = 0; i < 4; i++)
            {
                if ((gUnknown_3005E10.unk_30 >> i) & 1 && gUnknown_3005E10.unk_34[i] && --gUnknown_3005E10.unk_34[i] == 0)
                {
                    gUnknown_3005E10.unk_30 &= ~(1 << i);
                    flags |= (1 << i);
                }
            }
            if (flags)
            {
                sub_80FE818(flags);
                retVal = TRUE;
                gUnknown_3005E10.unk_14 = flags;
                sub_80FE7F0(0x33, 0x01);
            }
        }
        if (!gUnknown_3005E10.unk_30)
        {
            gUnknown_3005E10.unk_0a = 0;
        }
    }
    return retVal;
}

void rfu_syncVBlank_(void)
{
    if (rfu_syncVBlank())
    {
        sub_80FE7F0(0xF1, 0x00);
        sub_80FEAF4();
    }
}

void sub_80FDA30(u32 a0)
{
    u8 r2;

    if (gUnknown_3005E10.unk_40 == NULL && gUnknown_3005E10.unk_04 != 0)
    {
        gUnknown_3005E10.unk_04 = 0;
    }
    else
    {
        if (gUnknown_3005E10.unk_07 != 0)
        {
            sub_80FDC28(a0);
        }
        do
        {
            if (gUnknown_3005E10.unk_04 != 0)
            {
                rfu_waitREQComplete();
                gUnknown_3005E10.unk_0e = 1;
                switch (gUnknown_3005E10.unk_04)
                {
                case 23:
                    r2 = sub_80FD3A4() == 0x8001 ? 0x44 : 0xFF;
                    gUnknown_3005E10.unk_04 = gUnknown_3005E10.unk_05 = 0;
                    sub_80FE7F0(r2, 0);
                    break;
                case 1:
                    if (sub_80FD3A4() == 0x8001)
                    {
                        gUnknown_3005E10.unk_04 = gUnknown_3005E10.unk_05;
                        gUnknown_3005E10.unk_05 = 3;
                    }
                    else
                    {
                        gUnknown_3005E10.unk_04 = gUnknown_3005E10.unk_05 = 0;
                        sub_80FE7F0(0xFF, 0);
                    }
                    break;
                case 2:
                    rfu_REQ_reset();
                    break;
                case 3:
                    rfu_REQ_configSystem(gUnknown_3005E10.unk_3c->unk_02, gUnknown_3005E10.unk_3c->unk_00, gUnknown_3005E10.unk_3c->unk_01);
                    break;
                case 4:
                    rfu_REQ_configGameData(gUnknown_3005E10.unk_3c->unk_04, gUnknown_3005E10.unk_3c->unk_06, (const u8 *)gUnknown_3005E10.unk_3c->unk_08, gUnknown_3005E10.unk_3c->unk_0c);
                    break;
                case 5:
                    rfu_REQ_startSearchChild();
                    break;
                case 6:
                    rfu_REQ_pollSearchChild();
                    break;
                case 7:
                    rfu_REQ_endSearchChild();
                    break;
                case 8:
                    break;
                case 9:
                    rfu_REQ_startSearchParent();
                    break;
                case 10:
                    rfu_REQ_pollSearchParent();
                    break;
                case 11:
                    rfu_REQ_endSearchParent();
                    break;
                case 12:
                    rfu_REQ_startConnectParent(gUnknown_3005E10.unk_1e);
                    break;
                case 13:
                    rfu_REQ_pollConnectParent();
                    break;
                case 14:
                    rfu_REQ_endConnectParent();
                    break;
                case 15:
                    break;
                case 16:
                    rfu_REQ_CHILD_startConnectRecovery(gRfuLinkStatus->linkLossSlotFlag);
                    break;
                case 17:
                    rfu_REQ_CHILD_pollConnectRecovery();
                    break;
                case 18:
                    rfu_REQ_CHILD_endConnectRecovery();
                    break;
                case 19:
                    rfu_REQ_changeMasterSlave();
                    break;
                case 20:
                    break;
                case 21:
                    rfu_REQ_stopMode();
                    break;
                case 22:
                    break;
                }
                rfu_waitREQComplete();
                gUnknown_3005E10.unk_0e = 0;
            }
        } while (gUnknown_3005E10.unk_04 == 18 || gUnknown_3005E10.unk_04 == 19);
        if (gRfuLinkStatus->parentChild != 1 || !sub_80FD850(0))
        {
            sub_80FE418();
            sub_80FE63C();
            sub_80FE74C();
            sub_80FE918();
        }
    }
}

void sub_80FDC28(u32 a0)
{
    if (gUnknown_3005E10.unk_07 == 5)
    {
        gUnknown_3005E10.unk_06 = 1;
        gUnknown_3005E10.unk_04 = 5;
        gUnknown_3005E10.unk_1a = gUnknown_3005E10.unk_1c;
        if (gUnknown_3005E10.unk_1a)
        {
            gUnknown_3005E10.unk_07 = 6;
        }
        else
        {
            gUnknown_3005E10.unk_07 = 1;
        }
    }
    if (gUnknown_3005E10.unk_07 == 1)
    {
        gUnknown_3005E10.unk_06 = 1;
        gUnknown_3005E10.unk_04 = 5;
        gUnknown_3005E10.unk_1a = a0 % 140;
        gUnknown_3005E10.unk_1c = 140 - gUnknown_3005E10.unk_1a;
        if (gUnknown_3005E10.unk_1a)
        {
            gUnknown_3005E10.unk_07 = 2;
        }
        else
        {
            gUnknown_3005E10.unk_07 = 3;
        }
    }
    if (gUnknown_3005E10.unk_07 == 3)
    {
        gUnknown_3005E10.unk_06 = 0;
        gUnknown_3005E10.unk_1a = 40;
        gUnknown_3005E10.unk_07 = 4;
        gUnknown_3005E10.unk_04 = 9;
    }
}

void sub_80FDC98(u16 r8, u16 r6)
{
    u8 sp0;
    register u8 *stwiRecvBuffer asm("r0");
    u8 *tmp;
    u8 i;

    if (gUnknown_3005E10.unk_0e != 0)
    {
        gUnknown_3005E10.unk_0e = 0;
        switch (r8)
        {
        case 16:
            if (r6 == 0)
            {
                gUnknown_3005E10.unk_04 = gUnknown_3005E10.unk_05;
                gUnknown_3005E10.unk_05 = 4;
            }
            break;
        case 23:
            if (r6 == 0)
            {
                gUnknown_3005E10.unk_04 = gUnknown_3005E10.unk_05;
                gUnknown_3005E10.unk_05 = 0;
            }
            break;
        case 22:
            if (r6 == 0)
            {
                gUnknown_3005E10.unk_04 = gUnknown_3005E10.unk_05 = 0;
                sub_80FE7F0(0x00, 0x00);
            }
            break;
        case 25:
            if (r6 == 0)
            {
                gUnknown_3005E10.unk_04 = gUnknown_3005E10.unk_05 = 6;
            }
            break;
        case 26:
            if (gUnknown_3005E10.unk_1a && --gUnknown_3005E10.unk_1a == 0)
            {
                gUnknown_3005E10.unk_04 = 7;
                gUnknown_3005E10.unk_05 = 8;
            }
            break;
        case 27:
            if (r6 == 0)
            {
                gUnknown_3005E10.unk_04 = gUnknown_3005E10.unk_05;
                gUnknown_3005E10.unk_05 = 0;
                if (gUnknown_3005E10.unk_07 == 0)
                {
                    sub_80FE7F0(0x13, 0x00);
                }
            }
            break;
        case 28:
            if (r6 == 0)
            {
                if (gUnknown_3005E10.unk_0b == 1 && gUnknown_3005E10.unk_1a > 1)
                {
                    gUnknown_3005E10.unk_1a--;
                }
                gUnknown_3005E10.unk_04 = gUnknown_3005E10.unk_05 = 10;
            }
            break;
        case 29:
            if (r6 == 0)
            {
                sp0 = sub_80FE778();
                gUnknown_3005E10.unk_14 = sp0;
                if (sp0)
                {
                    sub_80FE7F0(0x20, 0x01);
                }
                if (gUnknown_3005E10.unk_0b && gUnknown_3005E10.unk_1a != 1 && gRfuLinkStatus->findParentCount == RFU_CHILD_MAX)
                {
                    rfu_REQ_endSearchParent();
                    rfu_waitREQComplete();
                    gUnknown_3005E10.unk_04 = 9;
                    gUnknown_3005E10.unk_0b = 1;
                }
            }
            if (gUnknown_3005E10.unk_1a && --gUnknown_3005E10.unk_1a == 0)
            {
                gUnknown_3005E10.unk_04 = 11;
                gUnknown_3005E10.unk_05 = 0;
            }
            break;
        case 30:
            if (r6 == 0)
            {
                gUnknown_3005E10.unk_04 = gUnknown_3005E10.unk_05;
                if (gUnknown_3005E10.unk_07 == 0)
                {
                    if (gUnknown_3005E10.unk_04 == 0)
                    {
                        sub_80FE7F0(0x21, 0x00);
                    }
                }
                else if (gUnknown_3005E10.unk_07 != 7)
                {
                    gUnknown_3005E10.unk_04 = 5;
                    gUnknown_3005E10.unk_07 = 5;
                }
            }
            break;
        case 31:
            if (r6 == 0)
            {
                gUnknown_3005E10.unk_04 = gUnknown_3005E10.unk_05 = 13;
            }
            break;
        case 32:
            if (r6 == 0 && !rfu_getConnectParentStatus(&sp0, &gUnknown_3005E10.unk_10) && !sp0)
            {
                gUnknown_3005E10.unk_04 = 14;
            }
            if (gUnknown_3005E10.unk_1a && --gUnknown_3005E10.unk_1a == 0)
            {
                gUnknown_3005E10.unk_04 = 14;
            }
            break;
        case 33:
            if (r6 == 0 && !rfu_getConnectParentStatus(&sp0, &gUnknown_3005E10.unk_10))
            {
                if (!sp0)
                {
                    gUnknown_3005E10.unk_04 = 19;
                    gUnknown_3005E10.unk_05 = 15;
                    gUnknown_3005E10.unk_1e = 0x22;
                    gUnknown_3005E10.unk_14 = gUnknown_3005E10.unk_10;
                }
                else
                {
                    gUnknown_3005E10.unk_04 = gUnknown_3005E10.unk_05 = 0;
                    gUnknown_3005E10.unk_1e = 0x23;
                    gUnknown_3005E10.unk_14 = sp0;
                    if (gUnknown_3005E10.unk_07)
                    {
                        gUnknown_3005E10.unk_07 = 3;
                        gUnknown_3005E10.unk_04 = 9;
                    }
                }
                sub_80FE7F0(gUnknown_3005E10.unk_1e, 0x01);
                gUnknown_3005E10.unk_1e = 0;
            }
            break;
        case 50:
            if (r6 == 0)
            {
                gUnknown_3005E10.unk_14 = gRfuLinkStatus->linkLossSlotFlag;
                gUnknown_3005E10.unk_04 = gUnknown_3005E10.unk_05 = 17;
                for (gUnknown_3005E10.unk_10 = 0; gUnknown_3005E10.unk_10 < 4; gUnknown_3005E10.unk_10 ++)
                {
                    if ((gRfuLinkStatus->linkLossSlotFlag >> gUnknown_3005E10.unk_10) & 1)
                    {
                        break;
                    }
                }
            }
            break;
        case 51:
            if (r6 == 0 && !rfu_CHILD_getConnectRecoveryStatus(&sp0) && sp0 < 2)
            {
                gUnknown_3005E10.unk_04 = 18;
            }
            if (gUnknown_3005E10.unk_34[gUnknown_3005E10.unk_10] && --gUnknown_3005E10.unk_34[gUnknown_3005E10.unk_10] == 0)
            {
                gUnknown_3005E10.unk_04 = 18;
            }
            break;
        case 52:
            if (r6 == 0 && !rfu_CHILD_getConnectRecoveryStatus(&sp0))
            {
                if (!sp0)
                {
                    gUnknown_3005E10.unk_04 = 19;
                    gUnknown_3005E10.unk_05 = 22;
                    gUnknown_3005E10.unk_1e = 0x32;
                }
                else
                {
                    gUnknown_3005E10.unk_04 = gUnknown_3005E10.unk_05 = 0;
                    sub_80FE818(gRfuLinkStatus->linkLossSlotFlag);
                    gUnknown_3005E10.unk_1e = 0x33;
                }
                gUnknown_3005E10.unk_34[gUnknown_3005E10.unk_10] = 0;
                gUnknown_3005E10.unk_30 = 0;
                gUnknown_3005E10.unk_0a = 0;
                sub_80FE7F0(gUnknown_3005E10.unk_1e, 0x01);
                gUnknown_3005E10.unk_1e = 0;
            }
            break;
        case 39:
            if (r6 == 0)
            {
                if (gUnknown_3005E10.unk_05 == 22)
                {
                    gUnknown_3005E10.unk_04 = gUnknown_3005E10.unk_11;
                    gUnknown_3005E10.unk_05 = gUnknown_3005E10.unk_12;
                    gUnknown_3005E10.unk_02 = 1;
                    sub_80FE7F0(0x41, 0x00);
                }
                else if (gUnknown_3005E10.unk_05 == 15)
                {
                    gUnknown_3005E10.unk_04 = gUnknown_3005E10.unk_05;
                    gUnknown_3005E10.unk_02 = 1;
                    sub_80FE7F0(0x41, 0x00);
                    gUnknown_3005E10.unk_24 |= 1 << gUnknown_3005E10.unk_10;
                    gUnknown_3005E10.unk_28[gUnknown_3005E10.unk_10] = gUnknown_3005E10.unk_26;
                    rfu_clearSlot(4, gUnknown_3005E10.unk_10);
                    tmp = &sp0;
                    *tmp = rfu_NI_CHILD_setSendGameName(gUnknown_3005E10.unk_10, 0x0e);
                    if (*tmp)
                    {
                        gUnknown_3005E10.unk_04 = gUnknown_3005E10.unk_05 = 0;
                        sub_80FEAF4();
                        sub_80FE818(gRfuLinkStatus->connSlotFlag | gRfuLinkStatus->linkLossSlotFlag);
                        gUnknown_3005E10.unk_14 = sp0;
                        sub_80FE7F0(0x25, 0x01);
                    }
                }
            }
            break;
        case 61:
            if (r6 == 0)
            {
                gUnknown_3005E10.unk_04 = gUnknown_3005E10.unk_05 = 0;
                sub_80FE7F0(0x42, 0x00);
            }
            break;
        }
        gUnknown_3005E10.unk_0e = 1;
    }
    else if (r6 == 3 && gUnknown_3005E10.unk_0f && (r8 == 0x24 || r8 == 0x26 || r8 == 0x27))
    {
        rfu_REQ_RFUStatus();
        rfu_waitREQComplete();
        rfu_getRFUStatus(&sp0);
        if (sp0 == 0 && gRfuLinkStatus->parentChild == MODE_CHILD)
        {
            stwiRecvBuffer = rfu_getSTWIRecvBuffer()->rxPacketAlloc.rfuPacket8.data;
            stwiRecvBuffer[4] = gRfuLinkStatus->connSlotFlag;
            stwiRecvBuffer[5] = 1;
            sub_80FD850(0x29);
            r6 = 0;
        }
    }
    switch (r8)
    {
    case 48:
        if (r6 == 0)
        {
            stwiRecvBuffer = rfu_getSTWIRecvBuffer()->rxPacketAlloc.rfuPacket8.data;
            gUnknown_3005E10.unk_14 = stwiRecvBuffer[8];
            sub_80FE83C(gUnknown_3005E10.unk_14);
            if (gUnknown_3005E10.unk_30)
            {
                gUnknown_3005E10.unk_30 &= ~gUnknown_3005E10.unk_14;
                for (i = 0; i < 4; i++)
                {
                    if ((gUnknown_3005E10.unk_14 >> i) & 1)
                    {
                        gUnknown_3005E10.unk_34[i] = 0;
                    }
                }
                if (gUnknown_3005E10.unk_06 == 0)
                {
                    gUnknown_3005E10.unk_04 = gUnknown_3005E10.unk_05 = 0;
                }
            }
            sp0 = gUnknown_3005E10.unk_00 & gUnknown_3005E10.unk_14;
            for (i = 0; i < 4; i++)
            {
                if ((sp0 >> i) & 1 && gUnknown_3005E10.unk_01)
                {
                    gUnknown_3005E10.unk_01--;
                }
            }
            gUnknown_3005E10.unk_00 &= ~gUnknown_3005E10.unk_14;
            if (gUnknown_3005E10.unk_07)
            {
                if (gRfuLinkStatus->parentChild == MODE_NEUTRAL)
                {
                    if (gUnknown_3005E10.unk_07 == 8)
                    {
                        gUnknown_3005E10.unk_1a = gUnknown_3005E10.unk_1c;
                        gUnknown_3005E10.unk_07 = 6;
                        gUnknown_3005E10.unk_04 = 6;
                    }
                    else if (gUnknown_3005E10.unk_04 != 6 && gUnknown_3005E10.unk_04 != 7)
                    {
                        gUnknown_3005E10.unk_07 = 1;
                        gUnknown_3005E10.unk_04 = 5;
                    }
                }
            }
            if (gRfuLinkStatus->parentChild == MODE_NEUTRAL)
            {
                if (gUnknown_3005E10.unk_04 == 0)
                {
                    gUnknown_3005E10.unk_06 = -1;
                }
            }
            if (gUnknown_3005E10.unk_0e == 0)
            {
                sub_80FE7F0(0x40, 0x01);
            }
        }
        break;
    case 38:
        sub_80FE6F0();
        if (gRfuLinkStatus->parentChild != MODE_NEUTRAL)
        {
            sub_80FE7F0(0x50, 0x00);
        }
        break;
    case 16:
    case 61:
        if (r6 == 0)
        {
            gUnknown_3005E10.unk_0d = 0;
            gUnknown_3005E10.unk_01 = 0;
            gUnknown_3005E10.unk_00 = 0;;
            gUnknown_3005E10.unk_06 = -1;
            sub_80FEAF4();
            if (r8 == 61)
            {
                sub_80FD484();
            }
        }
        break;
    }
    if (r6 != 0)
    {
        if (r8 == 28 && r6 != 0 && gUnknown_3005E10.unk_07 == 4)
        {
            gRfuLinkStatus->parentChild = MODE_PARENT;
            gRfuLinkStatus->connSlotFlag = 0xF;
            sub_80FE818(15);
            rfu_waitREQComplete();
            return;
        }
        else
        {
            gUnknown_3005E10.unk_14 = r8;
            gUnknown_3005E10.unk_16 = r6;
            if (gUnknown_3005E10.unk_0e)
            {
                gUnknown_3005E10.unk_04 = gUnknown_3005E10.unk_05 = 0;
            }
            sub_80FE7F0(0xf0, 0x02);
            sub_80FEAF4();
        }
    }
    if (r8 == 0xFF)
    {
        sub_80FE7F0(0xf2, 0x00);
        sub_80FEAF4();
    }
}

void sub_80FE394(u16 reqCommandId)
{
    u8 r7;
    u8 ackFlag;

    r7 = gUnknown_3005E10.unk_0e;
    gUnknown_3005E10.unk_0e = 0;
    gUnknown_3005E10.unk_0f = 1;
    if (gRfuLinkStatus->parentChild == MODE_CHILD)
    {
        sub_80FD850(reqCommandId);
        if (gUnknown_3005E10.unk_02 != 1)
        {
            sub_80FEAF4();
            gUnknown_3005E10.unk_0f = 0;
            gUnknown_3005E10.unk_0e = r7;
            return;
        }
    }
    else
    {
        if (!rfu_UNI_PARENT_getDRAC_ACK(&ackFlag))
        {
            gUnknown_3005E10.unk_03 |= ackFlag;
        }
    }
    if (gUnknown_3005E10.unk_44 != NULL)
    {
        gUnknown_3005E10.unk_44(reqCommandId);
        rfu_waitREQComplete();
        if (gUnknown_3005E10.unk_02 == 2)
        {
            sub_80FEAF4();
        }
    }
    gUnknown_3005E10.unk_0f = 0;
    gUnknown_3005E10.unk_0e = r7;
}

void sub_80FE418(void)
{
    u8 flags;
    u8 sp0;
    u8 i;
    u8 r5;
    u8 r4;
    const u16 *ptr;

    if (gUnknown_3005E10.unk_04 == 5 || gUnknown_3005E10.unk_04 == 6 || gUnknown_3005E10.unk_04 == 7 || gUnknown_3005E10.unk_04 == 8)
    {
        flags = ((gRfuLinkStatus->connSlotFlag ^ gUnknown_3005E10.unk_0c) & gRfuLinkStatus->connSlotFlag) & ~gRfuLinkStatus->getNameFlag;
        gUnknown_3005E10.unk_0c = gRfuLinkStatus->connSlotFlag;
        if (flags)
        {
            gUnknown_3005E10.unk_14 = flags;
            sub_80FE7F0(0x10, 0x01);
        }
        sp0 = 0x00;
        for (i = 0; i < 4; i++)
        {
            r4 = 1 << i;
            r5 = 0x00;
            if (flags & r4)
            {
                gUnknown_3005E10.unk_28[i] = gUnknown_3005E10.unk_26;
                gUnknown_3005E10.unk_24 |= r4;
            }
            else if (gUnknown_3005E10.unk_24 & r4)
            {
                if (gRfuSlotStatusNI[i]->recv.state == 0x46)
                {
                    if (gRfuSlotStatusNI[i]->recv.dataType == 1) // Game identification information
                    {
                        r5 = 0x02;
                        for (ptr = gUnknown_3005E10.unk_20; *ptr != 0xFFFF; ptr++)
                        {
                            if (gRfuLinkStatus->partner[i].serialNo == *ptr)
                            {
                                gUnknown_3005E10.unk_00 |= r4;
                                gUnknown_3005E10.unk_01++;
                                sp0 |= r4;
                                r5 |= 0x01;
                                break;
                            }
                        }
                        if (!(r5 & 0x01))
                        {
                            r5 |= 0x04;
                        }
                    }
                }
                else if (--gUnknown_3005E10.unk_28[i] == 0)
                {
                    r5 = 0x06;
                }
                if (r5 & 0x02)
                {
                    gUnknown_3005E10.unk_24 &= ~r4;
                    gUnknown_3005E10.unk_28[i] = 0;
                    rfu_clearSlot(0x08, i);
                }
                if (r5 & 0x04)
                {
                    gUnknown_3005E10.unk_0d |= r4;
                }
            }
        }
        if (sp0)
        {
            gUnknown_3005E10.unk_14 = sp0;
            sub_80FE7F0(0x11, 0x01);
        }
        if (gUnknown_3005E10.unk_0d)
        {
            r5 = 0x01;
            if (gRfuLinkStatus->sendSlotUNIFlag && ((gUnknown_3005E10.unk_03 & gUnknown_3005E10.unk_00) != gUnknown_3005E10.unk_00))
            {
                r5 = 0x00;
            }
            if (r5)
            {
                sub_80FE818(gUnknown_3005E10.unk_0d);
                gUnknown_3005E10.unk_14 = gUnknown_3005E10.unk_0d;
                gUnknown_3005E10.unk_0d = 0;
                sub_80FE7F0(0x12, 0x01);
            }
        }
        if (gUnknown_3005E10.unk_24 == 0 && gUnknown_3005E10.unk_04 == 8)
        {
            if (gUnknown_3005E10.unk_07 == 0)
            {
                gUnknown_3005E10.unk_04 = gUnknown_3005E10.unk_05 = 0;
                sub_80FE7F0(0x14, 0x00);
            }
            else
            {
                if (gUnknown_3005E10.unk_07 == 2)
                {
                    gUnknown_3005E10.unk_07 = 3;
                    gUnknown_3005E10.unk_04 = 9;
                }
                else
                {
                    gUnknown_3005E10.unk_07 = 1;
                    gUnknown_3005E10.unk_04 = 5;
                }
                if (gUnknown_3005E10.unk_00)
                {
                    gUnknown_3005E10.unk_1a = 0;
                    gUnknown_3005E10.unk_07 = 8;
                    gUnknown_3005E10.unk_04 = 5;
                }
            }
        }
    }
}

void sub_80FE63C(void)
{
    u16 imeBak = REG_IME;
    REG_IME = 0;
    if (gUnknown_3005E10.unk_04 == 15)
    {
        if (--gUnknown_3005E10.unk_28[gUnknown_3005E10.unk_10] == 0 || gRfuSlotStatusNI[gUnknown_3005E10.unk_10]->send.state == 0x27)
        {
            sub_80FEB14();
            gUnknown_3005E10.unk_04 = 24;
            rfu_clearSlot(4, gUnknown_3005E10.unk_10);
            gUnknown_3005E10.unk_24 &= ~(1 << gUnknown_3005E10.unk_10);
            gUnknown_3005E10.unk_28[gUnknown_3005E10.unk_10] = 0;
        }
    }
    REG_IME = imeBak;
    if (gUnknown_3005E10.unk_04 == 24)
    {
        if (gUnknown_3005E10.unk_02 == 1)
        {
            sub_80FEB14();
        }
        if (gUnknown_3005E10.unk_02 == 0)
        {
            gUnknown_3005E10.unk_04 = gUnknown_3005E10.unk_05 = 0;
            sub_80FE818(gRfuLinkStatus->connSlotFlag | gRfuLinkStatus->linkLossSlotFlag);
            gUnknown_3005E10.unk_14 = 0;
            sub_80FE7F0(0x25, 0x01);
        }
    }
}

void sub_80FE6F0(void)
{
    if (gUnknown_3005E10.unk_04 == 15 && gRfuSlotStatusNI[gUnknown_3005E10.unk_10]->send.state == 0x26)
    {
        gUnknown_3005E10.unk_04 = gUnknown_3005E10.unk_05 = 0;
        rfu_clearSlot(4, gUnknown_3005E10.unk_10);
        gUnknown_3005E10.unk_24 &= ~(1 << gUnknown_3005E10.unk_10);
        gUnknown_3005E10.unk_28[gUnknown_3005E10.unk_10] = 0;
        sub_80FE7F0(0x24, 0x00);
    }
}

void sub_80FE74C(void)
{
    if (gUnknown_3005E10.unk_06 == 0 && gUnknown_3005E10.unk_0a == 1)
    {
        gUnknown_3005E10.unk_11 = gUnknown_3005E10.unk_04;
        gUnknown_3005E10.unk_12 = gUnknown_3005E10.unk_05;
        gUnknown_3005E10.unk_04 = 16;
        gUnknown_3005E10.unk_05 = 17;
        gUnknown_3005E10.unk_0a = 2;
    }
}

u8 sub_80FE778(void)
{
    u8 i;
    const u16 *ptr;
    u8 flags = 0x00;

    for (i = 0; i < gRfuLinkStatus->findParentCount; i++)
    {
        for (ptr = gUnknown_3005E10.unk_20; *ptr != 0xFFFF; ptr++)
        {
            if (gRfuLinkStatus->partner[i].serialNo == *ptr)
            {
                flags |= (1 << i);
            }
        }
    }
    return flags;
}

void sub_80FE7F0(u8 a0, u8 a1)
{
    if (gUnknown_3005E10.unk_40 != NULL)
    {
        gUnknown_3005E10.unk_40(a0, a1);
    }
    gUnknown_3005E10.unk_14 = gUnknown_3005E10.unk_16 = 0;
}

void sub_80FE818(u8 a0)
{
    u8 unk_0e_bak = gUnknown_3005E10.unk_0e;
    gUnknown_3005E10.unk_0e = 1;
    rfu_REQ_disconnect(a0);
    rfu_waitREQComplete();
    gUnknown_3005E10.unk_0e = unk_0e_bak;
}

void sub_80FE83C(u8 a0)
{
    u8 i;

    if (gRfuLinkStatus->sendSlotNIFlag)
    {
        for (i = 0; i < 4; i++)
        {
            if (gRfuSlotStatusNI[i]->send.state & 0x8000 && gRfuSlotStatusNI[i]->send.bmSlot & a0)
            {
                rfu_changeSendTarget(0x20, i, gRfuSlotStatusNI[i]->send.bmSlot & ~a0);
            }
        }
    }
    if (gRfuLinkStatus->recvSlotNIFlag)
    {
        for (i = 0; i < 4; i++)
        {
            if (gRfuSlotStatusNI[i]->recv.state & 0x8000 && gRfuSlotStatusNI[i]->recv.bmSlot & a0)
            {
                rfu_NI_stopReceivingData(i);
            }
        }
    }
    if (gRfuLinkStatus->sendSlotUNIFlag)
    {
        gRfuLinkStatus->sendSlotUNIFlag &= ~a0;
        for (i = 0; i < 4; i++)
        {
            if (gRfuSlotStatusUNI[i]->send.state == 0x8024 && a0 & gRfuSlotStatusUNI[i]->send.bmSlot)
            {
                gRfuSlotStatusUNI[i]->send.bmSlot &= ~a0;
            }
        }
    }
}

void sub_80FE918(void)
{
    u8 i;
    u8 j;
    u8 flags;

    if (gUnknown_3005E10.unk_18)
    {
        if (gRfuLinkStatus->sendSlotNIFlag)
        {
            for (i = 0; i < 4; i ++)
            {
                if (gRfuSlotStatusNI[i]->send.state & 0x8000)
                {
                    flags = 0;
                    for (j = 0; j < 4; j++)
                    {
                        if ((gRfuSlotStatusNI[i]->send.bmSlot >> j) & 1 && gRfuSlotStatusNI[j]->send.failCounter > gUnknown_3005E10.unk_18)
                        {
                            flags |= (1 << j);
                        }
                        if (flags)
                        {
                            rfu_changeSendTarget(0x20, i, flags ^ gRfuSlotStatusNI[i]->send.bmSlot);
                        }
                    }
                }
            }
        }
        if (gRfuLinkStatus->recvSlotNIFlag)
        {
            for (i = 0; i < 4; i++)
            {
                if (gRfuSlotStatusNI[i]->recv.state & 0x8000 && gRfuSlotStatusNI[i]->recv.failCounter > gUnknown_3005E10.unk_18)
                {
                    rfu_NI_stopReceivingData(i);
                }
            }
        }
    }
}

void sub_80FEA10(void (*func)(u16))
{
    gUnknown_3005E10.unk_44 = func;
    rfu_setMSCCallback(sub_80FE394);
}

void sub_80FEA28(void (*func)(u8, u8))
{
    gUnknown_3005E10.unk_40 = func;
}

u8 sub_80FEA34(u8 a0, u16 a1)
{
    u16 imeBak;
    if (gUnknown_3005E10.unk_09 && a0 == 0 && gUnknown_3005E10.unk_30)
    {
        return 5;
    }
    imeBak = REG_IME;
    REG_IME = 0;
    gUnknown_3005E10.unk_09 = a0;
    gUnknown_3005E10.unk_32 = a1;
    REG_IME = imeBak;
    return 0;
}

u8 sub_80FEA78(u16 a0)
{
    if (gRfuLinkStatus->sendSlotNIFlag | gRfuLinkStatus->recvSlotNIFlag)
    {
        gUnknown_3005E10.unk_14 = 6;
        sub_80FE7F0(0xf3, 0x01);
        return 6;
    }
    gUnknown_3005E10.unk_18 = a0;
    return 0;
}

u8 sub_80FEAB4(u8 a0)
{
    if (gUnknown_3005E10.unk_04 == 9 || gUnknown_3005E10.unk_04 == 10 || gUnknown_3005E10.unk_04 == 11)
    {
        gUnknown_3005E10.unk_14 = 7;
        sub_80FE7F0(0xf3, 0x01);
        return 7;
    }
    if (a0)
    {
        gUnknown_3005E10.unk_0b = 1;
    }
    else
    {
        gUnknown_3005E10.unk_0b = 0;
    }
    return 0;
}

void sub_80FEAF4(void)
{
    if (gUnknown_3005E10.unk_02)
    {
        gUnknown_3005E10.unk_02 = 0;
        sub_80FE7F0(0x45, 0x00);
    }
}

void sub_80FEB14(void)
{
    if (gUnknown_3005E10.unk_02 == 0)
    {
        sub_80FE7F0(0x45, 0x00);
    }
    else if (gUnknown_3005E10.unk_02 == 1)
    {
        gUnknown_3005E10.unk_02 = 2;
    }
}

void sub_80FEB3C(void)
{
    if (gUnknown_3005E10.unk_07)
    {
        switch (gUnknown_3005E10.unk_04)
        {
        case 5:
            gUnknown_3005E10.unk_07 = 3;
            gUnknown_3005E10.unk_04 = 9;
            break;
        case 6:
            gUnknown_3005E10.unk_07 = 2;
            gUnknown_3005E10.unk_1a = 1;
            break;
        case 7:
        case 8:
            gUnknown_3005E10.unk_07 = 2;
            break;
        case 9:
        case 10:
            gUnknown_3005E10.unk_1a = 40;
            break;
        case 11:
            gUnknown_3005E10.unk_1a = 40;
            gUnknown_3005E10.unk_04 = 10;
            break;
        }
    }
}

