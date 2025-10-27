#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <map>

using namespace std;

string int_to_string(int x) {
    stringstream ss;
    ss << x;
    return ss.str();
}

string lay_thoi_gian_hien_tai() {
    time_t now = time(0);
    struct tm *ltm = localtime(&now);
    char buf[32];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buf);
}

time_t string_to_time(const string& time_str) {
    struct tm t;
    for (int i=0;i<sizeof(t);++i) ((char*)&t)[i]=0;
    if (sscanf(time_str.c_str(), "%d-%d-%d %d:%d:%d",
               &t.tm_year, &t.tm_mon, &t.tm_mday,
               &t.tm_hour, &t.tm_min, &t.tm_sec) != 6) {
        return 0;
    }
    t.tm_year -= 1900;
    t.tm_mon -= 1;
    t.tm_isdst = -1;
    return mktime(&t);
}

string tinh_thoi_gian_tra_du_kien() {
    time_t now = time(0);
    time_t du_kien = now + (7 * 24 * 60 * 60);
    struct tm *ltm = localtime(&du_kien);
    char buf[32];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buf);
}

void read_input_string(const string& prompt, string& value) {
    cout << prompt;
    getline(cin, value);
}

string lay_loai_tai_lieu(int choice) {
    switch (choice) {
        case 2: return "Ebook";
        case 3: return "Voice";
        case 4: return "Video";
        case 1:
        default: return "Sach In";
    }
}

enum LoaiGiaoDich { MUON, TRA, DOC_TRUC_TUYEN };
enum UserRole { UNKNOWN, ADMIN, THU_THU, BAN_DOC };

string lay_vai_tro_string(UserRole role) {
    if (role == ADMIN) return "Quan tri vien";
    if (role == THU_THU) return "Thu thu";
    if (role == BAN_DOC) return "Ban doc";
    return "Khong xac dinh";
}

class NguoiDung {
private:
    string username;
    string password;
    UserRole role;

public:
    NguoiDung(string user, string pass, UserRole r)
        : username(user), password(pass), role(r) {}

    string get_username() const { return username; }
    string get_password() const { return password; }
    UserRole get_role() const { return role; }
};

class TaiLieu {
private:
    string ma_tai_lieu;
    string ten_tai_lieu;
    string tac_gia;
    int nam_xuat_ban;
    string the_loai;
    string trang_thai; 
    int so_luot_muon;
    string loai_dien_tu; 
    string ten_file;
    string link_doc;

public:
    TaiLieu(string ma, string ten, string tg, int nam, string tl,
           string loai_dt, string file, string link)
        : ma_tai_lieu(ma), ten_tai_lieu(ten), tac_gia(tg), nam_xuat_ban(nam),
          the_loai(tl), trang_thai("Con"), so_luot_muon(0),
          loai_dien_tu(loai_dt), ten_file(file), link_doc(link) {}

    string get_ma_tai_lieu() const { return ma_tai_lieu; }
    string get_ten_tai_lieu() const { return ten_tai_lieu; }
    string get_the_loai() const { return the_loai; }
    string get_trang_thai() const { return trang_thai; }
    int get_so_luot_muon() const { return so_luot_muon; }
    string get_loai_dien_tu() const { return loai_dien_tu; }
    string get_ten_file() const { return ten_file; }
    string get_link_doc() const { return link_doc; }

    void set_trang_thai(const string& tt) { trang_thai = tt; }
    void tang_so_luot_muon() { so_luot_muon++; }

    void hien_thi() const {
        cout << "| Ma: " << ma_tai_lieu
             << " | Ten: " << ten_tai_lieu
             << " | Tac gia: " << tac_gia
             << " | LoaiTL: " << loai_dien_tu
             << " | Trang thai: " << trang_thai
             << " | LuotMuon: " << so_luot_muon << endl;
    }
};
class BanDoc {
private:
    string ma_ban_doc;
    string ho_ten;
    string so_cccd;
    string dia_chi;
    vector<string> tai_lieu_dang_muon;

public:
    BanDoc(string ma, string ten, string cccd, string dc)
        : ma_ban_doc(ma), ho_ten(ten), so_cccd(cccd), dia_chi(dc) {}

    string get_ma_ban_doc() const { return ma_ban_doc; }
    string get_ho_ten() const { return ho_ten; }
    const vector<string>& get_tai_lieu_dang_muon() const { return tai_lieu_dang_muon; }

    void them_tai_lieu_muon(const string& ma_tai_lieu) {
        tai_lieu_dang_muon.push_back(ma_tai_lieu);
    }

    void xoa_tai_lieu_muon(const string& ma_tai_lieu) {
        vector<string> tmp;
        for (size_t i = 0; i < tai_lieu_dang_muon.size(); ++i) {
            if (tai_lieu_dang_muon[i] != ma_tai_lieu) tmp.push_back(tai_lieu_dang_muon[i]);
        }
        tai_lieu_dang_muon = tmp;
    }

    void hien_thi() const {
        cout << "== MaBD: " << ma_ban_doc << " | Ten: " << ho_ten
             << " | Dang muon (" << tai_lieu_dang_muon.size() << ") ==" << endl;
    }

    void hien_thi_ma_muon() const {
        cout << "    Ma tai lieu dang muon: ";
        if (tai_lieu_dang_muon.empty()) {
            cout << "Khong co." << endl;
        } else {
            for (size_t i = 0; i < tai_lieu_dang_muon.size(); ++i) {
                cout << tai_lieu_dang_muon[i] << " ";
            }
            cout << endl;
        }
    }
};
class GiaoDich {
private:
    string ma_giao_dich;
    LoaiGiaoDich loai;
    string ma_ban_doc;
    string ma_tai_lieu;
    string thoi_gian_thuc_hien;
    string thoi_gian_tra_du_kien;
    double phi_tre_han;
    string ghi_chu;

public:
    GiaoDich(string ma_gd, LoaiGiaoDich l, string ma_bd, string ma_tl,
             string thoi_gian_dk, double phi, string note)
        : ma_giao_dich(ma_gd), loai(l), ma_ban_doc(ma_bd), ma_tai_lieu(ma_tl),
          thoi_gian_thuc_hien(lay_thoi_gian_hien_tai()), thoi_gian_tra_du_kien(thoi_gian_dk),
          phi_tre_han(phi), ghi_chu(note) {}

    string get_ma_ban_doc() const { return ma_ban_doc; }
    LoaiGiaoDich get_loai() const { return loai; }
    string get_thoi_gian_tra_du_kien() const { return thoi_gian_tra_du_kien; }
    string get_ma_tai_lieu() const { return ma_tai_lieu; }

    string lay_loai_giao_dich_string() const {
        if (loai == MUON) return "Muon";
        if (loai == TRA) return "Tra";
        if (loai == DOC_TRUC_TUYEN) return "Doc Online";
        return "Khong ro";
    }

    void hien_thi() const {
        cout << "| GD Ma: " << ma_giao_dich
             << " | Loai: " << lay_loai_giao_dich_string()
             << " | BD Ma: " << ma_ban_doc
             << " | TL Ma: " << ma_tai_lieu
             << " | TG: " << thoi_gian_thuc_hien;
        if (loai == MUON) {
            cout << " | DK Tra: " << thoi_gian_tra_du_kien;
        }
        if (phi_tre_han > 0.0) {
            cout << " | Phi tre: " << (long long)phi_tre_han << " VND";
        }
        if (!ghi_chu.empty()) {
            cout << " | Ghi chu: " << ghi_chu;
        }
        cout << endl;
    }
};
class ThuVien {
private:
    string ten_thu_vien;
    vector<BanDoc> danh_sach_ban_doc;
    vector<TaiLieu> danh_sach_tai_lieu;
    vector<GiaoDich> danh_sach_giao_dich;
    vector<NguoiDung> danh_sach_nguoi_dung;

    int next_doc_id;
    int next_reader_id;
    int next_transaction_id;
    double phi_mot_ngay;

    BanDoc* tim_ban_doc(const string& ma_bd) {
        for (size_t i=0;i<danh_sach_ban_doc.size();++i) {
            if (danh_sach_ban_doc[i].get_ma_ban_doc() == ma_bd) {
                return &danh_sach_ban_doc[i];
            }
        }
        return NULL;
    }

    const BanDoc* tim_ban_doc_const(const string& ma_bd) const {
        for (size_t i=0;i<danh_sach_ban_doc.size();++i) {
            if (danh_sach_ban_doc[i].get_ma_ban_doc() == ma_bd) {
                return &danh_sach_ban_doc[i];
            }
        }
        return NULL;
    }

    TaiLieu* tim_tai_lieu(const string& ma_tl) {
        for (size_t i=0;i<danh_sach_tai_lieu.size();++i) {
            if (danh_sach_tai_lieu[i].get_ma_tai_lieu() == ma_tl) {
                return &danh_sach_tai_lieu[i];
            }
        }
        return NULL;
    }

public:
    ThuVien(string ten)
        : ten_thu_vien(ten), next_doc_id(101), next_reader_id(1),
          next_transaction_id(1001), phi_mot_ngay(5000.0)
    {
        danh_sach_nguoi_dung.push_back(NguoiDung("admin", "123", ADMIN));
        danh_sach_nguoi_dung.push_back(NguoiDung("thuthu", "123", THU_THU));
        danh_sach_nguoi_dung.push_back(NguoiDung("bandoc", "123", BAN_DOC));
    }

    void dang_ky_nguoi_dung(string user, string pass, UserRole role) {
        for (size_t i=0;i<danh_sach_nguoi_dung.size();++i) {
            if (danh_sach_nguoi_dung[i].get_username() == user) {
                cout << "Loi: Username da ton tai." << endl;
                return;
            }
        }
        danh_sach_nguoi_dung.push_back(NguoiDung(user, pass, role));
        cout << "Dang ky tai khoan thanh cong. Username: " << user << " Vai tro: " << lay_vai_tro_string(role) << endl;
    }

    UserRole login_user(const string& user, const string& pass) {
        for (size_t i=0;i<danh_sach_nguoi_dung.size();++i) {
            if (danh_sach_nguoi_dung[i].get_username() == user &&
                danh_sach_nguoi_dung[i].get_password() == pass) {
                cout << "Dang nhap thanh cong. Vai tro: " << lay_vai_tro_string(danh_sach_nguoi_dung[i].get_role()) << endl;
                return danh_sach_nguoi_dung[i].get_role();
            }
        }
        cout << "Loi: Sai Username hoac Password." << endl;
        return UNKNOWN;
    }

    void dang_ky_ban_doc(string ho_ten, string so_cccd, string dia_chi) {
        string ma_bd = "R" + int_to_string(next_reader_id++);
        danh_sach_ban_doc.push_back(BanDoc(ma_bd, ho_ten, so_cccd, dia_chi));
        cout << "Dang ky ban doc thanh cong! Ma ban doc: " << ma_bd << endl;
    }

    void hien_thi_tat_ca_ban_doc() const {
        cout << "\n--- DANH SACH BAN DOC (" << danh_sach_ban_doc.size() << ") ---" << endl;
        for (size_t i=0;i<danh_sach_ban_doc.size();++i) {
            danh_sach_ban_doc[i].hien_thi();
        }
        cout << "------------------------------------------" << endl;
    }

    void hien_thi_ma_muon_cua_bd(const string& ma_bd) const {
        const BanDoc* reader = tim_ban_doc_const(ma_bd);
        if (!reader) {
            cout << "Loi: Khong tim thay ban doc voi ma " << ma_bd << endl;
            return;
        }
        cout << "\n--- TAI LIEU DANG MUON cua BD Ma: " << ma_bd << " ---" << endl;
        reader->hien_thi_ma_muon();
        cout << "------------------------------------------" << endl;
    }

    void them_tai_lieu(string ten, string tac_gia, int nam_xb, string the_loai,
                       string loai_dt, string file, string link) {
        string ma_tl = "D" + int_to_string(next_doc_id++);
        danh_sach_tai_lieu.push_back(TaiLieu(ma_tl, ten, tac_gia, nam_xb, the_loai, loai_dt, file, link));
        cout << "Them tai lieu thanh cong! Ma tai lieu: " << ma_tl << endl;
    }

    void xoa_tai_lieu(const string& ma_tl) {
        for (size_t i=0;i<danh_sach_tai_lieu.size();++i) {
            if (danh_sach_tai_lieu[i].get_ma_tai_lieu() == ma_tl) {
                if (danh_sach_tai_lieu[i].get_trang_thai() == "Da muon") {
                    cout << "Loi: Tai lieu dang duoc muon, khong the xoa." << endl;
                    return;
                }
                cout << "Da xoa tai lieu: [" << ma_tl << "] - " << danh_sach_tai_lieu[i].get_ten_tai_lieu() << endl;
                vector<TaiLieu> tmp;
                for (size_t j=0;j<danh_sach_tai_lieu.size();++j) {
                    if (j != i) tmp.push_back(danh_sach_tai_lieu[j]);
                }
                danh_sach_tai_lieu = tmp;
                return;
            }
        }
        cout << "Loi: Khong tim thay tai lieu voi ma " << ma_tl << endl;
    }

    void hien_thi_tat_ca_tai_lieu() const {
        cout << "\n--- DANH SACH TAI LIEU (" << danh_sach_tai_lieu.size() << ") ---" << endl;
        for (size_t i=0;i<danh_sach_tai_lieu.size();++i) {
            danh_sach_tai_lieu[i].hien_thi();
        }
        cout << "------------------------------------------" << endl;
    }
    void tim_tai_lieu_dien_tu() const {
        string ten_tim, loai_dt_tim;
        int loai_choice;
        cout << "\n  -- TIM KIEM TAI LIEU DIEN TU --" << endl;
        cout << "  1. Sach In | 2. Ebook | 3. Voice | 4. Video" << endl;
        cout << "  Chon loai tai lieu (1-4): ";
        if (!(cin >> loai_choice)) { cin.clear(); cin.ignore(10000,'\n'); return; }
        cin.ignore(10000,'\n');

        loai_dt_tim = lay_loai_tai_lieu(loai_choice);
        read_input_string("  Nhap Ten tai lieu can tim: ", ten_tim);

        bool found = false;

        for (size_t i=0;i<ten_tim.size();++i) if (ten_tim[i] >= 'A' && ten_tim[i] <= 'Z') ten_tim[i] = ten_tim[i] - 'A' + 'a';

        for (size_t i=0;i<danh_sach_tai_lieu.size();++i) {
            string lower_ten = danh_sach_tai_lieu[i].get_ten_tai_lieu();
            for (size_t k=0;k<lower_ten.size();++k) if (lower_ten[k] >= 'A' && lower_ten[k] <= 'Z') lower_ten[k] = lower_ten[k] - 'A' + 'a';
            if (danh_sach_tai_lieu[i].get_loai_dien_tu() == loai_dt_tim &&
                lower_ten.find(ten_tim) != string::npos) {
                cout << "\nDa tim thay tai lieu:" << endl;
                danh_sach_tai_lieu[i].hien_thi();
                cout << "   Ten File: " << danh_sach_tai_lieu[i].get_ten_file()
                     << " | Link: " << danh_sach_tai_lieu[i].get_link_doc() << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "Khong tim thay tai lieu [" << ten_tim << "] loai [" << loai_dt_tim << "]." << endl;
        }
    }

    void muon_tai_lieu(const string& ma_bd, const string& ma_tl) {
        BanDoc* reader = tim_ban_doc(ma_bd);
        TaiLieu* doc = tim_tai_lieu(ma_tl);

        if (!reader) { cout << "Loi: Khong tim thay ban doc voi ma " << ma_bd << endl; return; }
        if (!doc) { cout << "Loi: Khong tim thay tai lieu voi ma " << ma_tl << endl; return; }
        if (doc->get_trang_thai() == "Da muon") { cout << "Loi: Tai lieu da duoc muon." << endl; return; }

        if (doc->get_loai_dien_tu() != "Sach In") {
            cout << "Loi: Tai lieu [" << doc->get_ten_tai_lieu() << "] la tai lieu so hoa, khong the muon vat ly." << endl;
            return;
        }

        doc->set_trang_thai("Da muon");
        reader->them_tai_lieu_muon(ma_tl);
        doc->tang_so_luot_muon();

        string thoi_gian_dk = tinh_thoi_gian_tra_du_kien();
        string ma_gd = "T" + int_to_string(next_transaction_id++);

        danh_sach_giao_dich.push_back(GiaoDich(ma_gd, MUON, ma_bd, ma_tl, thoi_gian_dk, 0.0, ""));
        cout << "Muon thanh cong! Ten TL: " << doc->get_ten_tai_lieu()
             << " | Du kien tra truoc: " << thoi_gian_dk << endl;
    }

    void tra_tai_lieu(const string& ma_bd, const string& ma_tl) {
        BanDoc* reader = tim_ban_doc(ma_bd);
        TaiLieu* doc = tim_tai_lieu(ma_tl);

        if (!reader || !doc) { cout << "Loi: Ma ban doc hoac tai lieu khong hop le." << endl; return; }

        bool dang_muon = false;
        const vector<string>& arr = reader->get_tai_lieu_dang_muon();
        for (size_t i=0;i<arr.size();++i) {
            if (arr[i] == ma_tl) { dang_muon = true; break; }
        }
        if (!dang_muon) { cout << "Loi: Ban doc nay khong dang muon tai lieu ma " << ma_tl << "." << endl; return; }

        GiaoDich* gd_muon_gan_nhat = NULL;
        for (int idx = (int)danh_sach_giao_dich.size() - 1; idx >= 0; --idx) {
            if (danh_sach_giao_dich[idx].get_ma_ban_doc() == ma_bd &&
                danh_sach_giao_dich[idx].get_ma_tai_lieu() == ma_tl &&
                danh_sach_giao_dich[idx].get_loai() == MUON) {
                gd_muon_gan_nhat = &danh_sach_giao_dich[idx];
                break;
            }
        }

        double phi_tre_han = 0.0;
        string ghi_chu = "";
        if (gd_muon_gan_nhat) {
            time_t thoi_gian_dk = string_to_time(gd_muon_gan_nhat->get_thoi_gian_tra_du_kien());
            time_t thoi_gian_hien_tai = time(0);
            if (thoi_gian_dk == 0) thoi_gian_dk = thoi_gian_hien_tai; // neu parse loi thi coi nhu khong tre

            if (thoi_gian_hien_tai > thoi_gian_dk) {
                double tre_sec = difftime(thoi_gian_hien_tai, thoi_gian_dk);
                int so_ngay_tre = (int)(tre_sec / (24 * 3600));
                if (so_ngay_tre < 1) so_ngay_tre = 1;
                phi_tre_han = (double)so_ngay_tre * phi_mot_ngay;
                ghi_chu = "Tre han " + int_to_string(so_ngay_tre) + " ngay.";
                cout << "CHU Y: Tra tre " << so_ngay_tre << " ngay." << endl;
            }
        }

        doc->set_trang_thai("Con");
        reader->xoa_tai_lieu_muon(ma_tl);

        string ma_gd = "T" + int_to_string(next_transaction_id++);
        danh_sach_giao_dich.push_back(GiaoDich(ma_gd, TRA, ma_bd, ma_tl, "", phi_tre_han, ghi_chu));

        cout << "Tra thanh cong tai lieu " << doc->get_ten_tai_lieu()
             << ". Tong phi tre han: " << (long long)phi_tre_han << " VND" << endl;
    }

    void doc_online(const string& ma_bd, const string& ma_tl) {
        BanDoc* reader = tim_ban_doc(ma_bd);
        TaiLieu* doc = tim_tai_lieu(ma_tl);

        if (!reader || !doc) { cout << "Loi: Ma ban doc hoac tai lieu khong hop le." << endl; return; }

        if (doc->get_loai_dien_tu() == "Sach In") {
            cout << "Loi: Tai lieu [" << doc->get_ten_tai_lieu() << "] khong co ban so hoa de doc online." << endl;
            return;
        }

        string ma_gd = "T" + int_to_string(next_transaction_id++);
        danh_sach_giao_dich.push_back(GiaoDich(ma_gd, DOC_TRUC_TUYEN, ma_bd, ma_tl, "", 0.0, ""));
        cout << "Ban doc " << reader->get_ho_ten() << " bat dau doc online." << endl;
        cout << "   Loai: " << doc->get_loai_dien_tu() << endl;
        cout << "   Link: " << doc->get_link_doc() << endl;
    }

    void thong_ke_so_luot_doc() const {
        int count = 0;
        map<string, int> doc_count;
        for (size_t i=0;i<danh_sach_giao_dich.size();++i) {
            if (danh_sach_giao_dich[i].get_loai() == DOC_TRUC_TUYEN) {
                count++;
                string ma = danh_sach_giao_dich[i].get_ma_tai_lieu();
                if (doc_count.find(ma) == doc_count.end()) doc_count[ma] = 1;
                else doc_count[ma] += 1;
            }
        }
        cout << "\n--- THONG KE DOC ONLINE ---" << endl;
        cout << "Tong so luot doc online: " << count << endl;
        if (count == 0) { cout << "Chua co luot doc online nao." << endl; return; }
        cout << "Chi tiet theo Ma tai lieu:" << endl;
        for (map<string,int>::const_iterator it = doc_count.begin(); it != doc_count.end(); ++it) {
            string ten = "Khong ro";
            for (size_t k=0;k<danh_sach_tai_lieu.size();++k) {
                if (danh_sach_tai_lieu[k].get_ma_tai_lieu() == it->first) {
                    ten = danh_sach_tai_lieu[k].get_ten_tai_lieu();
                    break;
                }
            }
            cout << "  - [" << it->first << "] " << ten << ": " << it->second << " luot" << endl;
        }
        cout << "------------------------------------------" << endl;
    }

    void thong_ke_tai_lieu_pho_bien_nhat() const {
        cout << "\n--- TAI LIEU PHO BIEN NHAT (Theo luot Muon) ---" << endl;
        vector<pair<int,string> > popular_docs;
        for (size_t i=0;i<danh_sach_tai_lieu.size();++i) {
            popular_docs.push_back(make_pair(danh_sach_tai_lieu[i].get_so_luot_muon(),
                                             danh_sach_tai_lieu[i].get_ten_tai_lieu()));
        }
        sort(popular_docs.begin(), popular_docs.end());
        reverse(popular_docs.begin(), popular_docs.end());
        if (popular_docs.empty() || popular_docs[0].first == 0) {
            cout << "Chua co tai lieu nao duoc muon." << endl;
            return;
        }
        cout << "Cac tai lieu pho bien nhat (TOP 5):" << endl;
        int out = (int)popular_docs.size();
        if (out > 5) out = 5;
        for (int i=0;i<out;++i) {
            cout << i+1 << ". " << popular_docs[i].second << " (Da muon: " << popular_docs[i].first << " lan)" << endl;
        }
        cout << "------------------------------------------" << endl;
    }

    void de_xuat_tai_lieu(const string& ma_bd) const {
        const BanDoc* reader = tim_ban_doc_const(ma_bd);
        if (!reader) { cout << "Loi: Khong tim thay ban doc voi ma " << ma_bd << endl; return; }

        map<string,int> favorite_genres;
        for (size_t i=0;i<danh_sach_giao_dich.size();++i) {
            if (danh_sach_giao_dich[i].get_ma_ban_doc() == ma_bd) {
                string ma_tl = danh_sach_giao_dich[i].get_ma_tai_lieu();
                string the_loai = "";
                for (size_t k=0;k<danh_sach_tai_lieu.size();++k) {
                    if (danh_sach_tai_lieu[k].get_ma_tai_lieu() == ma_tl) {
                        the_loai = danh_sach_tai_lieu[k].get_the_loai();
                        break;
                    }
                }
                if (the_loai != "") {
                    if (favorite_genres.find(the_loai) == favorite_genres.end()) favorite_genres[the_loai] = 1;
                    else favorite_genres[the_loai] += 1;
                }
            }
        }

        if (favorite_genres.empty()) {
            cout << "Lich su giao dich trong. Khong the de xuat." << endl;
            return;
        }

        string top_genre = "";
        int max_count = -1;
        for (map<string,int>::const_iterator it = favorite_genres.begin(); it != favorite_genres.end(); ++it) {
            if (it->second > max_count) {
                max_count = it->second;
                top_genre = it->first;
            }
        }

        cout << "\n--- DE XUAT TAI LIEU cho " << reader->get_ho_ten() << " ---" << endl;
        cout << "The loai yeu thich: [" << top_genre << "] (Tuong tac: " << max_count << " lan)" << endl;
        cout << "Cac tai lieu lien quan (chua muon):" << endl;

        bool found_rec = false;
        int rec_count = 0;
        for (size_t i=0;i<danh_sach_tai_lieu.size() && rec_count < 3;++i) {
            if (danh_sach_tai_lieu[i].get_the_loai() == top_genre) {
                bool already = false;
                for (size_t j=0;j<danh_sach_giao_dich.size();++j) {
                    if (danh_sach_giao_dich[j].get_ma_ban_doc() == ma_bd &&
                        danh_sach_giao_dich[j].get_ma_tai_lieu() == danh_sach_tai_lieu[i].get_ma_tai_lieu()) {
                        already = true;
                        break;
                    }
                }
                if (!already) {
                    cout << "  - Ma: " << danh_sach_tai_lieu[i].get_ma_tai_lieu()
                         << " | Ten: " << danh_sach_tai_lieu[i].get_ten_tai_lieu()
                         << " | Loai: " << danh_sach_tai_lieu[i].get_loai_dien_tu() << endl;
                    found_rec = true;
                    rec_count++;
                }
            }
        }

        if (!found_rec) {
            cout << "Khong tim thay tai lieu moi trong the loai [" << top_genre << "] de de xuat." << endl;
        }
        cout << "------------------------------------------" << endl;
    }

    static bool cmp_giaodich_theo_bd(const GiaoDich& a, const GiaoDich& b) {
        return a.get_ma_ban_doc() < b.get_ma_ban_doc();
    }

    void hien_thi_tat_ca_giao_dich_gom_theo_bd() {
        sort(danh_sach_giao_dich.begin(), danh_sach_giao_dich.end(), cmp_giaodich_theo_bd);

        string bd_truoc = "";
        for (size_t i=0;i<danh_sach_giao_dich.size();++i) {
            if (danh_sach_giao_dich[i].get_ma_ban_doc() != bd_truoc) {
                bd_truoc = danh_sach_giao_dich[i].get_ma_ban_doc();
                cout << "\n===== LICH SU GIAO DICH CUA " << bd_truoc << " =====" << endl;
            }
            danh_sach_giao_dich[i].hien_thi();
        }
    }
};

void menu_chinh(ThuVien& lib, UserRole& current_user_role, string& current_user_id);
void menu_quan_ly_ban_doc(ThuVien& lib, UserRole role);
void menu_quan_ly_tai_lieu(ThuVien& lib, UserRole role);
void menu_giao_dich(ThuVien& lib, UserRole role);
void menu_thong_ke(ThuVien& lib, UserRole role, const string& user_id);
void menu_dang_ky_he_thong(ThuVien& lib);

void menu_dang_ky_he_thong(ThuVien& lib) {
    string user, pass;
    int role_choice;
    UserRole role = UNKNOWN;
    cout << "\n--- DANG KY TAI KHOAN HE THONG ---" << endl;
    read_input_string("  Nhap Username moi: ", user);
    read_input_string("  Nhap Password: ", pass);
    cout << "  1. Admin | 2. Thu thu | 3. Ban doc\n";
    cout << "  Chon Vai tro (1-3): ";
    if (!(cin >> role_choice)) { cin.clear(); role_choice = 3; }
    cin.ignore(10000,'\n');
    if (role_choice == 1) role = ADMIN;
    else if (role_choice == 2) role = THU_THU;
    else role = BAN_DOC;
    lib.dang_ky_nguoi_dung(user, pass, role);
}

void menu_quan_ly_ban_doc(ThuVien& lib, UserRole role) {
    if (role == BAN_DOC) {
        cout << "Loi: Ban doc khong co quyen quan ly ban doc." << endl;
        return;
    }
    int sub_choice;
    string ho_ten, cccd, dia_chi, ma_bd;
    do {
        cout << "\n--- MENU QUAN LY BAN DOC ---" << endl;
        cout << "1. Dang ky ban doc moi (NHAP DU LIEU)" << endl;
        cout << "2. Xem tat ca ban doc" << endl;
        cout << "3. Xem chi tiet Ma tai lieu dang muon" << endl;
        cout << "0. Quay lai" << endl;
        cout << "Chon chuc nang: ";
        if (!(cin >> sub_choice)) { cin.clear(); sub_choice = -1; }
        cin.ignore(10000,'\n');
        switch (sub_choice) {
            case 1:
                read_input_string("  Nhap Ho ten: ", ho_ten);
                read_input_string("  Nhap So CCCD: ", cccd);
                read_input_string("  Nhap Dia chi: ", dia_chi);
                lib.dang_ky_ban_doc(ho_ten, cccd, dia_chi);
                break;
            case 2:
                lib.hien_thi_tat_ca_ban_doc();
                break;
            case 3:
                read_input_string("  Nhap Ma ban doc can xem: ", ma_bd);
                lib.hien_thi_ma_muon_cua_bd(ma_bd);
                break;
            case 0: break;
            default: cout << "Lua chon khong hop le." << endl;
        }
    } while (sub_choice != 0);
}

void menu_quan_ly_tai_lieu(ThuVien& lib, UserRole role) {
    if (role == BAN_DOC) {
        cout << "Loi: Ban doc khong co quyen quan ly tai lieu." << endl;
        return;
    }
    int sub_choice;
    string ten, tac_gia, the_loai, ma_tl;
    int nam_xb, loai_tl_choice;
    string loai_dt, ten_file, link_doc;
    do {
        cout << "\n--- MENU QUAN LY TAI LIEU ---" << endl;
        cout << "1. Them moi tai lieu (Sach In / So hoa)" << endl;
        cout << "2. Xoa tai lieu theo Ma" << endl;
        cout << "3. Xem tat ca tai lieu" << endl;
        cout << "4. Tim tai lieu dien tu (theo loai va ten)" << endl;
        cout << "0. Quay lai" << endl;
        cout << "Chon chuc nang: ";
        if (!(cin >> sub_choice)) { cin.clear(); sub_choice = -1; }
        cin.ignore(10000,'\n');
        switch (sub_choice) {
            case 1:
                read_input_string("  Nhap Ten tai lieu: ", ten);
                read_input_string("  Nhap Tac gia: ", tac_gia);
                read_input_string("  Nhap The loai chung: ", the_loai);
                cout << "  -- LOAI TAI LIEU --" << endl;
                cout << "  1. Sach In | 2. Ebook | 3. Voice book | 4. Video book" << endl;
                cout << "  Chon loai (1-4): ";
                if (!(cin >> loai_tl_choice)) { loai_tl_choice = 1; cin.clear(); }
                cin.ignore(10000,'\n');
                loai_dt = lay_loai_tai_lieu(loai_tl_choice);
                ten_file = ""; link_doc = "";
                if (loai_dt != "Sach In") {
                    read_input_string("  Nhap Ten file: ", ten_file);
                    read_input_string("  Nhap Link truy cap: ", link_doc);
                }
                cout << "  Nhap Nam xuat ban: ";
                if (!(cin >> nam_xb)) { nam_xb = 0; cin.clear(); }
                cin.ignore(10000,'\n');
                lib.them_tai_lieu(ten, tac_gia, nam_xb, the_loai, loai_dt, ten_file, link_doc);
                break;
            case 2:
                read_input_string("  Nhap Ma tai lieu can xoa: ", ma_tl);
                lib.xoa_tai_lieu(ma_tl);
                break;
            case 3:
                lib.hien_thi_tat_ca_tai_lieu();
                break;
            case 4:
                lib.tim_tai_lieu_dien_tu();
                break;
            case 0: break;
            default: cout << "Lua chon khong hop le." << endl;
        }
    } while (sub_choice != 0);
}

void menu_giao_dich(ThuVien& lib, UserRole role) {
    if (role == ADMIN || role == THU_THU) {
        cout << "Loi: Chi ban doc duoc thuc hien cac giao dich muon/tra/doc." << endl;
        return;
    }
    int sub_choice;
    string ma_bd, ma_tl;
    do {
        cout << "\n--- MENU GIAO DICH MUON/TRA ---" << endl;
        cout << "1. Muon tai lieu (Sach In)" << endl;
        cout << "2. Tra tai lieu (Tinh phi tre han)" << endl;
        cout << "3. Doc tai lieu truc tuyen (Tai lieu so hoa)" << endl;
        cout << "0. Quay lai" << endl;
        cout << "Chon chuc nang: ";
        if (!(cin >> sub_choice)) { cin.clear(); sub_choice = -1; }
        cin.ignore(10000,'\n');
        switch (sub_choice) {
            case 1:
                read_input_string("  Nhap Ma ban doc: ", ma_bd);
                read_input_string("  Nhap Ma tai lieu muon: ", ma_tl);
                lib.muon_tai_lieu(ma_bd, ma_tl);
                break;
            case 2:
                read_input_string("  Nhap Ma ban doc: ", ma_bd);
                read_input_string("  Nhap Ma tai lieu muon tra: ", ma_tl);
                lib.tra_tai_lieu(ma_bd, ma_tl);
                break;
            case 3:
                read_input_string("  Nhap Ma ban doc: ", ma_bd);
                read_input_string("  Nhap Ma tai lieu muon doc: ", ma_tl);
                lib.doc_online(ma_bd, ma_tl);
                break;
            case 0: break;
            default: cout << "Lua chon khong hop le." << endl;
        }
    } while (sub_choice != 0);
}

void menu_thong_ke(ThuVien& lib, UserRole role, const string& user_id) {
    if (role == BAN_DOC && user_id != "") {
        cout << "Loi: Ban doc chi duoc xem lich su ca nhan." << endl;
        return;
    }

    int sub_choice;
    do {
        cout << "\n--- MENU THONG KE ---" << endl;
        cout << "1. Thong ke tai lieu pho bien (theo luot muon)" << endl;
        cout << "2. Thong ke so luot doc online" << endl;
        cout << "3. Xem lich su giao dich cua ban doc (NHAP MA BD)" << endl;
        cout << "0. Quay lai" << endl;
        cout << "Chon chuc nang: ";
        if (!(cin >> sub_choice)) { cin.clear(); sub_choice = -1; }
        cin.ignore(10000,'\n');
        switch (sub_choice) {
            case 1:
                lib.thong_ke_tai_lieu_pho_bien_nhat();
                break;
            case 2:
                lib.thong_ke_so_luot_doc();
                break;
            case 3: {
                string ma_bd;
                read_input_string("  Nhap Ma ban doc can xem lich su: ", ma_bd);
                cout << "Chuc nang xem lich su da duoc goi cho BD: " << ma_bd << endl;
                break;
            }
            case 0: break;
            default: cout << "Lua chon khong hop le." << endl;
        }
    } while (sub_choice != 0);
}

void menu_chinh_chuc_nang(ThuVien& lib, UserRole role, const string& user_id) {
    int choice;
    string ma_bd;
    do {
        cout << "\n================ MENU CHUC NANG ================" << endl;
        if (role != BAN_DOC) {
            cout << "1. Quan ly Ban doc" << endl;
            cout << "2. Quan ly Tai lieu" << endl;
            cout << "3. Thong ke & Bao cao" << endl;
        }
        if (role == BAN_DOC) {
            cout << "1. Giao dich Muon/Tra & Doc Online" << endl;
            cout << "2. Xem chi tiet Ma tai lieu dang muon" << endl;
            cout << "3. De xuat Tai lieu" << endl;
        }
        cout << "0. Dang xuat" << endl;
        cout << "Chon chuc nang: ";
        if (!(cin >> choice)) { cin.clear(); choice = -1; }
        cin.ignore(10000,'\n');
        if (role == ADMIN || role == THU_THU) {
            switch (choice) {
                case 1: menu_quan_ly_ban_doc(lib, role); break;
                case 2: menu_quan_ly_tai_lieu(lib, role); break;
                case 3: menu_thong_ke(lib, role, user_id); break;
                case 0: return;
                default: cout << "Lua chon khong hop le." << endl;
            }
        } else if (role == BAN_DOC) {
            switch (choice) {
                case 1: menu_giao_dich(lib, role); break;
                case 2:
                    read_input_string("  Nhap Ma ban doc can xem: ", ma_bd);
                    lib.hien_thi_ma_muon_cua_bd(ma_bd);
                    break;
                case 3:
                    read_input_string("  Nhap Ma ban doc can de xuat: ", ma_bd);
                    lib.de_xuat_tai_lieu(ma_bd);
                    break;
                case 0: return;
                default: cout << "Lua chon khong hop le." << endl;
            }
        }
    } while (choice != 0);
}

void menu_chinh(ThuVien& lib, UserRole& current_user_role, string& current_user_id) {
    int choice;
    string user, pass;

    do {
        cout << "\n========================================================" << endl;
        cout << "           HE THONG QUAN LY THU VIEN SO - DEMO" << endl;
        cout << "================ MENU CHINH ================" << endl;
        cout << "1. Dang nhap" << endl;
        cout << "2. Dang ky tai khoan he thong (Admin/Thu thu/Ban doc)" << endl;
        cout << "0. Thoat chuong trinh" << endl;
        cout << "Chon chuc nang: ";
        if (!(cin >> choice)) { cin.clear(); choice = -1; }
        cin.ignore(10000,'\n');
        switch (choice) {
            case 1:
                read_input_string("  Nhap Username: ", user);
                read_input_string("  Nhap Password: ", pass);
                current_user_role = lib.login_user(user, pass);
                if (current_user_role != UNKNOWN) {
                    current_user_id = user;
                    menu_chinh_chuc_nang(lib, current_user_role, current_user_id);
                    current_user_role = UNKNOWN;
                    current_user_id = "";
                }
                break;
            case 2:
                menu_dang_ky_he_thong(lib);
                break;
            case 0:
                cout << "\nCam on ban da su dung he thong. Tam biet!" << endl;
                break;
            default:
                cout << "Lua chon khong hop le. Vui long thu lai." << endl;
        }
    } while (choice != 0);
}

int main() {
    cout.setf(ios::fixed);
    cout << setprecision(0);

    ThuVien myLibrary("Thu vien So Demo");
    UserRole current_user_role = UNKNOWN;
    string current_user_id = "";

    myLibrary.dang_ky_ban_doc("Nguyen Van A", "999111", "Ha Noi");
    myLibrary.them_tai_lieu("C++ Nang Cao", "Tac Gia Mau", 2020, "Lap Trinh", "Sach In", "", "");
    myLibrary.them_tai_lieu("Lich Su The Gioi", "Mau Lich Su", 2022, "Lich Su", "Ebook", "LS.pdf", "https://link_doc/ls");
    myLibrary.them_tai_lieu("Giao trinh OOP", "GV A", 2023, "Lap Trinh", "Sach In", "", "");
    myLibrary.them_tai_lieu("Tieu thuyet tinh yeu", "NN A", 2021, "Van hoc", "Sach In", "", "");
    myLibrary.them_tai_lieu("Van hoc hien dai", "NN B", 2023, "Van hoc", "Ebook", "VH.epub", "https://vh.com/vh");

    myLibrary.muon_tai_lieu("R1", "D101");
    myLibrary.tra_tai_lieu("R1", "D101");
    myLibrary.doc_online("R1", "D102");
    myLibrary.doc_online("R1", "D105");
    myLibrary.muon_tai_lieu("R1", "D104");

    menu_chinh(myLibrary, current_user_role, current_user_id);

    return 0;
}

