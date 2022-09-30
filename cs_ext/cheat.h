#pragma once


class rcs {
public:

    // easier and more clean for our main
    __forceinline void starting() {
        hProcID = proc->procId(L"csgo.exe");// grabbing our proc


        hProc = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, false, hProcID);// opening a handle to csgo

        while (proc->GetModBaseAddy(hProcID, L"client.dll") == 0)//when our client isnt loaded yet
            Sleep(100);

        while (proc->GetModBaseAddy(hProcID, L"engine.dll") == 0)//when our engine isnt loaded yet
            Sleep(100);

        cout << "Found The Process By: " << hProcID << endl; // giving a ouput to the user to notify them the process was found
    }

    __forceinline void recoil() {

        const auto dwClientStatePtr = m->read<uintptr_t>(eng + offsets::dwClientState);
        const auto dwClientState_State = m->read<uintptr_t>(dwClientStatePtr + offsets::dwClientState_State);
        cli = proc->GetModBaseAddy(hProcID, L"client.dll");
        eng = proc->GetModBaseAddy(hProcID, L"engine.dll");

        if (dwClientState_State == 6) {// SignOnState = 6
            const auto dwlocal = m->read<uintptr_t>(cli + offsets::dwLocalPlayer);
            if (dwlocal != 0) {
                const auto dwPunch = m->read<vec3>(dwlocal + offsets::m_aimPunchAngle);
                const auto dwViewAngles = m->read<vec3>(dwClientStatePtr + offsets::dwClientState_ViewAngles);
                const float OutputPunch = dwPunch.x + dwPunch.y;

                if (OutputPunch != 0.f) { //finding the punch from our angles
                    const auto NewAngles = vec3{ ((dwViewAngles.x + dwOldPunchAngle.x) - (dwPunch.x * 2.f)),((dwViewAngles.y + dwOldPunchAngle.y) - (dwPunch.y * 2.f)),0.f };//Creating a New Angle To View
                    const auto aimAngle = ClampAngle(NewAngles);//clamping New Angle

                    m->write<vec3>(dwClientStatePtr + offsets::dwClientState_ViewAngles, aimAngle);// writing that clamped angle 
                    dwOldPunchAngle = vec3{ dwPunch.x * 2.f, dwPunch.y * 2.f, 0.f };
                }
                else {// if we dont have no recoil then we set dwoldpunch back to 0
                    dwOldPunchAngle = vec3{ 0.f, 0.f, 0.f };
                }
            }
        }
    }
};
