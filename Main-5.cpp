#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <map>
#include <cmath>

using namespace std;

string lay_thoi_gian_hien_tai() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << put_time(ltm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

time_t string_to_time(const string& time_str) {
    tm t{};
    if (strptime(time_str.c_str(), "%Y-%m-%d %H:%M:%S", &t) == nullptr) {
        return 0;
    }
    t.tm_isdst = -1;
    return mktime(&t);
}

string tinh_thoi_gian_tra_du_kien() {
    time_t now = time(0);
    time_t du_kien = now + (7 * 24 * 60 * 60); 
    
    tm* ltm = localtime(&du_kien);
    stringstream ss;
    ss << put_time(ltm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
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

enum class LoaiGiaoDich { MUON, TRA, DOC_TRUC_TUYEN };

enum class UserRole { UNKNOWN, ADMIN, THU_THU, BAN_DOC };

string lay_vai_tro_string(UserRole role) {
    if (role == UserRole::ADMIN) return "Quản trị viên";
    if (role == UserRole::THU_THU) return "Thủ thư";
    if (role == UserRole::BAN_DOC) return "Bạn đọc";
    return "Không xác định";
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
    int so_luot_muon = 0; 
    
    string loai_dien_tu; 
    string ten_file;
    string link_doc;

public:
    TaiLieu(string ma, string ten, string tg, int nam, string tl,
            string loai_dt = "Sach In", string file = "", string link = "")
        : ma_tai_lieu(ma), ten_tai_lieu(ten), tac_gia(tg), nam_xuat_ban(nam), the_loai(tl), trang_thai("Còn"),
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
        cout << "| Mã: " << ma_tai_lieu
             << " | Tên: " << ten_tai_lieu
             << " | Tác giả: " << tac_gia
             << " | Loại TL: " << loai_dien_tu 
             << " | Trạng thái: " << trang_thai 
             << " | Lượt Mượn: " << so_luot_muon << endl;
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
        tai_lieu_dang_muon.erase(
            remove(tai_lieu_dang_muon.begin(), tai_lieu_dang_muon.end(), ma_tai_lieu),
            tai_lieu_dang_muon.end()
        );
    }
    
    void hien_thi() const {
        cout << "== Mã BD: " << ma_ban_doc << " | Tên: " << ho_ten 
             << " | Đang mượn (" << tai_lieu_dang_muon.size() << ") ==" << endl;
    }

    void hien_thi_ma_muon() const {
        cout << "    Mã tài liệu đang mượn: ";
        if (tai_lieu_dang_muon.empty()) {
            cout << "Không có." << endl;
        } else {
            for (const auto& ma : tai_lieu_dang_muon) {
                cout << ma << " ";
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
                string thoi_gian_dk = "", double phi = 0.0, string note = "")
        : ma_giao_dich(ma_gd), loai(l), ma_ban_doc(ma_bd), ma_tai_lieu(ma_tl),
          thoi_gian_thuc_hien(lay_thoi_gian_hien_tai()), thoi_gian_tra_du_kien(thoi_gian_dk),
          phi_tre_han(phi), ghi_chu(note) {}

    string get_ma_ban_doc() const { return ma_ban_doc; }
    LoaiGiaoDich get_loai() const { return loai; }
    string get_thoi_gian_tra_du_kien() const { return thoi_gian_tra_du_kien; }
    string get_ma_tai_lieu() const { return ma_tai_lieu; }

    string lay_loai_giao_dich_string() const {
        if (loai == LoaiGiaoDich::MUON) return "Mượn";
        if (loai == LoaiGiaoDich::TRA) return "Trả";
        if (loai == LoaiGiaoDich::DOC_TRUC_TUYEN) return "Đọc Online";
        return "Không rõ";
    }

    void hien_thi() const {
        cout << "| GD Mã: " << ma_giao_dich
             << " | Loại: " << lay_loai_giao_dich_string()
             << " | BD Mã: " << ma_ban_doc
             << " | TL Mã: " << ma_tai_lieu
             << " | TG: " << thoi_gian_thuc_hien;
        
        if (loai == LoaiGiaoDich::MUON) {
            cout << " | DK Trả: " << thoi_gian_tra_du_kien;
        }
        if (phi_tre_han > 0) {
            cout << " | Phí trễ: " << fixed << setprecision(0) << phi_tre_han << " VND";
        }
        if (!ghi_chu.empty()) {
            cout << " | Ghi chú: " << ghi_chu;
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
    
    int next_doc_id = 101;
    int next_reader_id = 1;
    int next_transaction_id = 1001;
    const double phi_mot_ngay = 5000.0;

    BanDoc* tim_ban_doc(const string& ma_bd) {
        for (auto& bd : danh_sach_ban_doc) {
            if (bd.get_ma_ban_doc() == ma_bd) {
                return &bd;
            }
        }
        return nullptr;
    }

    const BanDoc* tim_ban_doc(const string& ma_bd) const {
        for (const auto& bd : danh_sach_ban_doc) {
            if (bd.get_ma_ban_doc() == ma_bd) {
                return &bd;
            }
        }
        return nullptr;
    }

    TaiLieu* tim_tai_lieu(const string& ma_tl) {
        for (auto& tl : danh_sach_tai_lieu) {
            if (tl.get_ma_tai_lieu() == ma_tl) {
                return &tl;
            }
        }
        return nullptr;
    }

public:
    ThuVien(string ten) : ten_thu_vien(ten) {
        danh_sach_nguoi_dung.emplace_back("admin", "123", UserRole::ADMIN);
        danh_sach_nguoi_dung.emplace_back("thuthu", "123", UserRole::THU_THU);
        danh_sach_nguoi_dung.emplace_back("bandoc", "123", UserRole::BAN_DOC);
    }
    
    void dang_ky_nguoi_dung(string user, string pass, UserRole role) {
        for (const auto& nd : danh_sach_nguoi_dung) {
            if (nd.get_username() == user) {
                cout << " Lỗi: Username đã tồn tại." << endl;
                return;
            }
        }
        danh_sach_nguoi_dung.emplace_back(user, pass, role);
        cout << " Đăng ký tài khoản [" << lay_vai_tro_string(role) << "] thành công! Username: " << user << endl;
    }

    UserRole login_user(const string& user, const string& pass) {
        for (const auto& nd : danh_sach_nguoi_dung) {
            if (nd.get_username() == user && nd.get_password() == pass) {
                cout << "Đăng nhập thành công! Vai trò: " << lay_vai_tro_string(nd.get_role()) << endl;
                return nd.get_role();
            }
        }
        cout << " Lỗi: Sai Username hoặc Password." << endl;
        return UserRole::UNKNOWN;
    }

    void dang_ky_ban_doc(string ho_ten, string so_cccd, string dia_chi) {
        string ma_bd = "R" + to_string(next_reader_id++);
        danh_sach_ban_doc.emplace_back(ma_bd, ho_ten, so_cccd, dia_chi);
        cout << "Đăng ký bạn đọc thành công! Mã bạn đọc: " << ma_bd << endl;
    }
    
    void hien_thi_tat_ca_ban_doc() const {
        cout << "\n--- DANH SÁCH BẠN ĐỌC (" << danh_sach_ban_doc.size() << ") ---" << endl;
        for (const auto& reader : danh_sach_ban_doc) {
            reader.hien_thi();
        }
        cout << "----------------------------------------------------------" << endl;
    }

    void hien_thi_ma_muon_cua_bd(const string& ma_bd) const {
        const BanDoc* reader = tim_ban_doc(ma_bd); // SỬ DỤNG PHIÊN BẢN CONST
        if (!reader) {
            cout << " Lỗi: Không tìm thấy bạn đọc với mã " << ma_bd << endl;
            return;
        }
        cout << "\n--- TÀI LIỆU ĐANG MƯỢN của BD Mã: " << ma_bd << " ---" << endl;
        reader->hien_thi_ma_muon();
        cout << "---------------------------------------------------------" << endl;
    }

    void them_tai_lieu(string ten, string tac_gia, int nam_xb, string the_loai,
                        string loai_dt, string file, string link) { 
        string ma_tl = "D" + to_string(next_doc_id++);
        danh_sach_tai_lieu.emplace_back(ma_tl, ten, tac_gia, nam_xb, the_loai, loai_dt, file, link); 
        cout << "Thêm tài liệu thành công! Mã tài liệu: " << ma_tl << endl;
    }
    
    void xoa_tai_lieu(const string& ma_tl) {
        for (auto it = danh_sach_tai_lieu.begin(); it != danh_sach_tai_lieu.end(); ++it) {
            if (it->get_ma_tai_lieu() == ma_tl) {
                if (it->get_trang_thai() == "Đã mượn") {
                    cout << " Lỗi: Tài liệu đang được mượn, không thể xóa." << endl;
                    return;
                }
                cout << " Đã xóa tài liệu: [" << ma_tl << "] - " << it->get_ten_tai_lieu() << endl;
                danh_sach_tai_lieu.erase(it);
                return;
            }
        }
        cout << " Lỗi: Không tìm thấy tài liệu với mã " << ma_tl << endl;
    }

    void hien_thi_tat_ca_tai_lieu() const {
        cout << "\n--- DANH SÁCH TÀI LIỆU (" << danh_sach_tai_lieu.size() << ") ---" << endl;
        for (const auto& doc : danh_sach_tai_lieu) {
            doc.hien_thi();
        }
        cout << "----------------------------------------------------------" << endl;
    }
    
    void tim_tai_lieu_dien_tu() const {
        string ten_tim, loai_dt_tim;
        int loai_choice;

        cout << "\n  -- TÌM KIẾM TÀI LIỆU ĐIỆN TỬ --" << endl;
        cout << "  1. Sách In | 2. Ebook | 3. Voice | 4. Video" << endl;
        cout << "  Chọn loại tài liệu cần tìm (1-4): "; 
        if (!(cin >> loai_choice)) { cin.clear(); cin.ignore(10000, '\n'); return; }
        cin.ignore(10000, '\n');

        loai_dt_tim = lay_loai_tai_lieu(loai_choice);

        read_input_string("  Nhập Tên tài liệu cần tìm: ", ten_tim);

        bool found = false;
        string lower_ten_tim = ten_tim;
        transform(lower_ten_tim.begin(), lower_ten_tim.end(), lower_ten_tim.begin(), ::tolower);

        for (const auto& tl : danh_sach_tai_lieu) {
            string lower_ten_tl = tl.get_ten_tai_lieu();
            transform(lower_ten_tl.begin(), lower_ten_tl.end(), lower_ten_tl.begin(), ::tolower);

            if (tl.get_loai_dien_tu() == loai_dt_tim && lower_ten_tl.find(lower_ten_tim) != string::npos) {
                cout << "\n Đã tìm thấy tài liệu:" << endl;
                tl.hien_thi();
                cout << "   Tên File: " << tl.get_ten_file() << " | Link: " << tl.get_link_doc() << endl;
                found = true;
            }
        }

        if (!found) {
            cout << " Không tìm thấy tài liệu [" << ten_tim << "] loại [" << loai_dt_tim << "]." << endl;
        }
    }

    void muon_tai_lieu(const string& ma_bd, const string& ma_tl) {
        BanDoc* reader = tim_ban_doc(ma_bd);
        TaiLieu* doc = tim_tai_lieu(ma_tl);

        if (!reader) { cout << " Lỗi: Không tìm thấy bạn đọc với mã " << ma_bd << endl; return; }
        if (!doc) { cout << " Lỗi: Không tìm thấy tài liệu với mã " << ma_tl << endl; return; }
        if (doc->get_trang_thai() == "Đã mượn") { cout << " Lỗi: Tài liệu đã được mượn." << endl; return; }
        
        if (doc->get_loai_dien_tu() != "Sach In") {
            cout << " Lỗi: Tài liệu [" << doc->get_ten_tai_lieu() << "] là tài liệu số hóa, không thể mượn vật lý." << endl;
            return;
        }

        doc->set_trang_thai("Đã mượn");
        reader->them_tai_lieu_muon(ma_tl);
        doc->tang_so_luot_muon(); 

        string thoi_gian_dk = tinh_thoi_gian_tra_du_kien();
        string ma_gd = "T" + to_string(next_transaction_id++);
        
        danh_sach_giao_dich.emplace_back(ma_gd, LoaiGiaoDich::MUON, ma_bd, ma_tl, thoi_gian_dk);

        cout << " Mượn thành công! Tên TL: " << doc->get_ten_tai_lieu() 
             << " | Dự kiến trả trước: " << thoi_gian_dk << endl;
    }

    void tra_tai_lieu(const string& ma_bd, const string& ma_tl) {
        BanDoc* reader = tim_ban_doc(ma_bd);
        TaiLieu* doc = tim_tai_lieu(ma_tl);

        if (!reader || !doc) { cout << " Lỗi: Mã bạn đọc hoặc tài liệu không hợp lệ." << endl; return; }
        
        bool dang_muon = false;
        for (const auto& ma : reader->get_tai_lieu_dang_muon()) {
            if (ma == ma_tl) {
                dang_muon = true;
                break;
            }
        }
        if (!dang_muon) { 
            cout << " Lỗi: Bạn đọc này không đang mượn tài liệu có mã " << ma_tl << "." << endl; 
            return; 
        }

        GiaoDich* gd_muon_gan_nhat = nullptr;
        for (auto it = danh_sach_giao_dich.rbegin(); it != danh_sach_giao_dich.rend(); ++it) {
            if (it->get_ma_ban_doc() == ma_bd && it->get_ma_tai_lieu() == ma_tl && it->get_loai() == LoaiGiaoDich::MUON) {
                gd_muon_gan_nhat = &(*it);
                break;
            }
        }
        
        double phi_tre_han = 0.0;
        string ghi_chu = "";
        if (gd_muon_gan_nhat) {
            time_t thoi_gian_dk = string_to_time(gd_muon_gan_nhat->get_thoi_gian_tra_du_kien());
            time_t thoi_gian_hien_tai = time(0);

            if (thoi_gian_hien_tai > thoi_gian_dk) {
                double tre_sec = difftime(thoi_gian_hien_tai, thoi_gian_dk);
                int so_ngay_tre = tre_sec / (24 * 3600); 
                if (so_ngay_tre < 1) so_ngay_tre = 1; 

                phi_tre_han = so_ngay_tre * phi_mot_ngay;
                ghi_chu = "Tre han " + to_string(so_ngay_tre) + " ngay.";

                cout << "CHÚ Ý: Trả trễ " << so_ngay_tre << " ngày." << endl;
            }
        }

        doc->set_trang_thai("Còn");
        reader->xoa_tai_lieu_muon(ma_tl);

        string ma_gd = "T" + to_string(next_transaction_id++);
        danh_sach_giao_dich.emplace_back(ma_gd, LoaiGiaoDich::TRA, ma_bd, ma_tl, "", phi_tre_han, ghi_chu);

        cout << "Trả thành công tài liệu " << doc->get_ten_tai_lieu() 
             << ". Tổng phí trễ hạn: " << fixed << setprecision(0) << phi_tre_han << " VNĐ" << endl;
    }

    void doc_online(const string& ma_bd, const string& ma_tl) {
        BanDoc* reader = tim_ban_doc(ma_bd);
        TaiLieu* doc = tim_tai_lieu(ma_tl);

        if (!reader || !doc) { cout << "Lỗi: Mã bạn đọc hoặc tài liệu không hợp lệ." << endl; return; }
        
        if (doc->get_loai_dien_tu() == "Sach In") { 
             cout << "Lỗi: Tài liệu [" << doc->get_ten_tai_lieu() << "] không có bản số hóa để đọc trực tuyến." << endl;
             return;
        }

        string ma_gd = "T" + to_string(next_transaction_id++);
        danh_sach_giao_dich.emplace_back(ma_gd, LoaiGiaoDich::DOC_TRUC_TUYEN, ma_bd, ma_tl);
        
        cout << " Bạn đọc " << reader->get_ho_ten() << " bắt đầu đọc trực tuyến." << endl;
        cout << "   Loại: " << doc->get_loai_dien_tu() << endl;
        cout << "   Link truy cập: " << doc->get_link_doc() << endl;
    }
    
    void thong_ke_so_luot_doc() const {
        int count = 0;
        map<string, int> doc_count; 

        for (const auto& trans : danh_sach_giao_dich) {
            if (trans.get_loai() == LoaiGiaoDich::DOC_TRUC_TUYEN) {
                count++;
                doc_count[trans.get_ma_tai_lieu()]++;
            }
        }

        cout << "\n--- THỐNG KÊ ĐỌC ONLINE ---" << endl;
        cout << " Tổng số lượt đọc online: " << count << endl;
        if (count == 0) { cout << "Chưa có lượt đọc online nào." << endl; return; }
        
        cout << " Chi tiết theo Mã tài liệu:" << endl;
        for (const auto& pair : doc_count) {
            TaiLieu* doc = const_cast<ThuVien*>(this)->tim_tai_lieu(pair.first); 
            cout << "  - [" << pair.first << "] " << (doc ? doc->get_ten_tai_lieu() : "Không rõ") 
                 << ": " << pair.second << " lượt" << endl;
        }
        cout << "------------------------------------------" << endl;
    }

    void thong_ke_tai_lieu_pho_bien_nhat() const {
        cout << "\n--- TÀI LIỆU PHỔ BIẾN NHẤT (Theo lượt Mượn) ---" << endl;
        
        vector<pair<int, string>> popular_docs;

        for (const auto& doc : danh_sach_tai_lieu) {
            popular_docs.push_back({doc.get_so_luot_muon(), doc.get_ten_tai_lieu()});
        }

        sort(popular_docs.rbegin(), popular_docs.rend());

        if (popular_docs.empty() || popular_docs[0].first == 0) {
            cout << "Chưa có tài liệu nào được mượn." << endl;
            return;
        }

        cout << "Các tài liệu phổ biến nhất (TOP 5):" << endl;
        for (size_t i = 0; i < min((size_t)5, popular_docs.size()); ++i) { 
            cout << i + 1 << ". " << popular_docs[i].second 
                 << " (Đã mượn: " << popular_docs[i].first << " lần)" << endl;
        }
        cout << "------------------------------------------" << endl;
    }
    
    void de_xuat_tai_lieu(const string& ma_bd) const {
        const BanDoc* reader = tim_ban_doc(ma_bd); 
        if (!reader) { cout << " Lỗi: Không tìm thấy bạn đọc với mã " << ma_bd << endl; return; }

        map<string, int> favorite_genres;
        for (const auto& trans : danh_sach_giao_dich) {
            if (trans.get_ma_ban_doc() == ma_bd) {
                TaiLieu* doc = const_cast<ThuVien*>(this)->tim_tai_lieu(trans.get_ma_tai_lieu());
                if (doc) {
                    favorite_genres[doc->get_the_loai()]++;
                }
            }
        }

        if (favorite_genres.empty()) {
            cout << "Lịch sử giao dịch trống. Không thể đề xuất." << endl;
            return;
        }

        string top_genre = "";
        int max_count = -1;
        for (const auto& pair : favorite_genres) {
            if (pair.second > max_count) {
                max_count = pair.second;
                top_genre = pair.first;
            }
        }

        cout << "\n--- ĐỀ XUẤT TÀI LIỆU cho " << reader->get_ho_ten() << " ---" << endl;
        cout << "Thể loại yêu thích nhất: [" << top_genre << "] (Tương tác: " << max_count << " lần)" << endl;
        cout << "Các tài liệu liên quan (chưa mượn):" << endl;

        bool found_rec = false;
        int rec_count = 0;
        for (const auto& doc : danh_sach_tai_lieu) {
            if (doc.get_the_loai() == top_genre) {
                bool already_interacted = false;
                for (const auto& trans : danh_sach_giao_dich) {
                    if (trans.get_ma_ban_doc() == ma_bd && trans.get_ma_tai_lieu() == doc.get_ma_tai_lieu()) {
                        already_interacted = true;
                        break;
                    }
                }
                
                if (!already_interacted && rec_count < 3) { 
                    cout << "  - Mã: " << doc.get_ma_tai_lieu() << " | Tên: " << doc.get_ten_tai_lieu() 
                         << " | Loại: " << doc.get_loai_dien_tu() << endl;
                    found_rec = true;
                    rec_count++;
                }
            }
        }

        if (!found_rec) {
            cout << "Không tìm thấy tài liệu mới trong thể loại [" << top_genre << "] để đề xuất." << endl;
        }
        cout << "------------------------------------------" << endl;
    }
};

void menu_chinh(ThuVien& lib, UserRole& current_user_role, string& current_user_id);
void menu_quan_ly_ban_doc(ThuVien& lib, UserRole role);
void menu_quan_ly_tai_lieu(ThuVien& lib, UserRole role);
void menu_giao_dich(ThuVien& lib, UserRole role);
void menu_thong_ke(ThuVien& lib, UserRole role, const string& user_id);

void menu_dang_ky_he_thong(ThuVien& lib) {
    string user, pass, ma_bd;
    int role_choice;
    UserRole role = UserRole::UNKNOWN;

    cout << "\n--- ĐĂNG KÝ TÀI KHOẢN HỆ THỐNG ---" << endl;
    read_input_string("  Nhập Username mới: ", user);
    read_input_string("  Nhập Password: ", pass);
    cout << "  1. Admin | 2. Thủ thư | 3. Bạn đọc\n";
    cout << "  Chọn Vai trò (1-3): ";
    
    if (!(cin >> role_choice)) { cin.clear(); role_choice = 3; }
    cin.ignore(10000, '\n');

    if (role_choice == 1) role = UserRole::ADMIN;
    else if (role_choice == 2) role = UserRole::THU_THU;
    else role = UserRole::BAN_DOC;
    
    lib.dang_ky_nguoi_dung(user, pass, role);
}

void menu_quan_ly_ban_doc(ThuVien& lib, UserRole role) {
    if (role == UserRole::BAN_DOC) {
        cout << " Lỗi: Bạn đọc không có quyền quản lý bạn đọc khác." << endl;
        return;
    }

    int sub_choice;
    string ho_ten, cccd, dia_chi;
    string ma_bd;

    do {
        cout << "\n--- MENU QUẢN LÝ BẠN ĐỌC ---" << endl;
        cout << "1. Đăng ký bạn đọc mới (NHẬP DỮ LIỆU)" << endl;
        cout << "2. Xem tất cả bạn đọc" << endl;
        cout << "3. Xem chi tiết Mã tài liệu đang mượn" << endl; 
        cout << "0. Quay lại" << endl;
        cout << "Chọn chức năng: ";
        
        if (!(cin >> sub_choice)) { 
            cin.clear(); 
            sub_choice = -1;
        }
        cin.ignore(10000, '\n');

        switch (sub_choice) {
            case 1:
                read_input_string("  Nhập Họ tên: ", ho_ten);
                read_input_string("  Nhập Số CCCD: ", cccd);
                read_input_string("  Nhập Địa chỉ: ", dia_chi);
                lib.dang_ky_ban_doc(ho_ten, cccd, dia_chi);
                break;
            case 2:
                lib.hien_thi_tat_ca_ban_doc();
                break;
            case 3: 
                read_input_string("  Nhập Mã bạn đọc cần xem: ", ma_bd);
                lib.hien_thi_ma_muon_cua_bd(ma_bd);
                break;
            case 0: break;
            default: cout << "Lựa chọn không hợp lệ." << endl;
        }
    } while (sub_choice != 0);
}

void menu_quan_ly_tai_lieu(ThuVien& lib, UserRole role) {
    if (role == UserRole::BAN_DOC) {
        cout << " Lỗi: Bạn đọc không có quyền quản lý tài liệu." << endl;
        return;
    }

    int sub_choice;
    string ten, tac_gia, the_loai, ma_tl;
    int nam_xb, loai_tl_choice;
    string loai_dt, ten_file, link_doc;

    do {
        cout << "\n--- MENU QUẢN LÝ TÀI LIỆU ---" << endl;
        cout << "1. Thêm mới tài liệu (Sách In/Số hóa)" << endl;
        cout << "2. Xóa tài liệu theo Mã" << endl; 
        cout << "3. Xem tất cả tài liệu" << endl;
        cout << "4. Tìm kiếm Tài liệu Điện tử (theo loại và tên)" << endl; 
        cout << "0. Quay lại" << endl;
        cout << "Chọn chức năng: ";
        
        if (!(cin >> sub_choice)) { 
            cin.clear(); 
            sub_choice = -1;
        }
        cin.ignore(10000, '\n'); 

        switch (sub_choice) {
            case 1:
                read_input_string("  Nhập Tên tài liệu: ", ten);
                read_input_string("  Nhập Tác giả: ", tac_gia);
                read_input_string("  Nhập Thể loại chung: ", the_loai);
                
                cout << "  -- LOẠI TÀI LIỆU --" << endl;
                cout << "  1. Sách In (Vật lý) | 2. Ebook | 3. Voice book | 4. Video book" << endl;
                cout << "  Chọn loại (1-4): "; 
                if (!(cin >> loai_tl_choice)) { loai_tl_choice = 1; cin.clear(); }
                cin.ignore(10000, '\n');
                
                loai_dt = lay_loai_tai_lieu(loai_tl_choice);
                ten_file = ""; link_doc = "";

                if (loai_dt != "Sach In") {
                    read_input_string("  Nhập Tên file: ", ten_file);
                    read_input_string("  Nhập Link truy cập: ", link_doc);
                }
                
                cout << "  Nhập Năm xuất bản: "; 
                if (!(cin >> nam_xb)) { nam_xb = 0; cin.clear(); }
                cin.ignore(10000, '\n');

                lib.them_tai_lieu(ten, tac_gia, nam_xb, the_loai, loai_dt, ten_file, link_doc);
                break;
            case 2: 
                read_input_string("  Nhập Mã tài liệu cần xóa: ", ma_tl);
                lib.xoa_tai_lieu(ma_tl);
                break;
            case 3:
                lib.hien_thi_tat_ca_tai_lieu();
                break;
            case 4: 
                lib.tim_tai_lieu_dien_tu(); 
                break;
            case 0: break;
            default: cout << "Lựa chọn không hợp lệ." << endl;
        }
    } while (sub_choice != 0);
}

void menu_giao_dich(ThuVien& lib, UserRole role) {
    if (role == UserRole::ADMIN || role == UserRole::THU_THU) {
        cout << " Lỗi: Chỉ bạn đọc mới được thực hiện các giao dịch mượn/đọc." << endl;
        return;
    }
    
    int sub_choice;
    string ma_bd, ma_tl;

    do {
        cout << "\n--- MENU GIAO DỊCH MƯỢN/TRẢ ---" << endl;
        cout << "1. Mượn tài liệu (Sách In)" << endl;
        cout << "2. Trả tài liệu (Sách In, Tính phí trễ hạn)" << endl;
        cout << "3. Đọc tài liệu trực tuyến (Tài liệu Số hóa)" << endl;
        cout << "0. Quay lại" << endl;
        cout << "Chọn chức năng: ";
        
        if (!(cin >> sub_choice)) { 
            cin.clear(); 
            sub_choice = -1;
        }
        cin.ignore(10000, '\n'); 

        switch (sub_choice) {
            case 1:
                read_input_string("  Nhập Mã bạn đọc: ", ma_bd);
                read_input_string("  Nhập Mã tài liệu muốn mượn: ", ma_tl);
                lib.muon_tai_lieu(ma_bd, ma_tl);
                break;
            case 2:
                read_input_string("  Nhập Mã bạn đọc: ", ma_bd);
                read_input_string("  Nhập Mã tài liệu muốn trả: ", ma_tl);
                lib.tra_tai_lieu(ma_bd, ma_tl);
                break;
            case 3:
                read_input_string("  Nhập Mã bạn đọc: ", ma_bd);
                read_input_string("  Nhập Mã tài liệu muốn đọc: ", ma_tl);
                lib.doc_online(ma_bd, ma_tl); 
                break;
            case 0: break;
            default: cout << "Lựa chọn không hợp lệ." << endl;
        }
    } while (sub_choice != 0);
}

void menu_thong_ke(ThuVien& lib, UserRole role, const string& user_id) {
    if (role == UserRole::BAN_DOC && user_id != "") {
        cout << " Lỗi: Bạn đọc chỉ được xem lịch sử giao dịch cá nhân." << endl;
        return;
    }

    int sub_choice;

    do {
        cout << "\n--- MENU THỐNG KÊ ---" << endl;
        cout << "1. Thống kê tài liệu phổ biến nhất (theo lượt mượn)" << endl;
        cout << "2. Thống kê số lượt đọc online" << endl;
        cout << "3. Xem lịch sử giao dịch của bạn đọc (NHẬP MÃ BD)" << endl;
        cout << "0. Quay lại" << endl;
        cout << "Chọn chức năng: ";
        
        if (!(cin >> sub_choice)) { 
            cin.clear(); 
            sub_choice = -1;
        }
        cin.ignore(10000, '\n');

        switch (sub_choice) {
            case 1:
                lib.thong_ke_tai_lieu_pho_bien_nhat();
                break;
            case 2:
                lib.thong_ke_so_luot_doc();
                break;
            case 3: {
                string ma_bd;
                read_input_string("  Nhập Mã bạn đọc cần xem lịch sử: ", ma_bd);
                cout << "Chức năng xem lịch sử đã được gọi cho BD: " << ma_bd << endl;
                break;
            }
            case 0: break;
            default: cout << "Lựa chọn không hợp lệ." << endl;
        }
    } while (sub_choice != 0);
}

void menu_chinh_chuc_nang(ThuVien& lib, UserRole role, const string& user_id) {
    int choice;
    string ma_bd;

    do {
        cout << "\n================ MENU CHỨC NĂNG ================" << endl;
        if (role != UserRole::BAN_DOC) {
            cout << "1. Quản lý Bạn đọc" << endl;
            cout << "2. Quản lý Tài liệu" << endl;
            cout << "3. Thống kê & Báo cáo" << endl;
        }
        if (role == UserRole::BAN_DOC) {
            cout << "1. Giao dịch Mượn/Trả & Đọc Online" << endl;
            cout << "2. Xem chi tiết Mã tài liệu đang mượn" << endl;
            cout << "3. Đề xuất Tài liệu" << endl; 
        }
        cout << "0. Đăng xuất" << endl;
        cout << "Chọn chức năng: ";

        if (!(cin >> choice)) {
            cin.clear();
            choice = -1;
        }
        cin.ignore(10000, '\n');

        if (role == UserRole::ADMIN || role == UserRole::THU_THU) {
            switch (choice) {
                case 1: menu_quan_ly_ban_doc(lib, role); break;
                case 2: menu_quan_ly_tai_lieu(lib, role); break;
                case 3: menu_thong_ke(lib, role, user_id); break;
                case 0: return;
                default: cout << "Lựa chọn không hợp lệ." << endl;
            }
        } else if (role == UserRole::BAN_DOC) {
            switch (choice) {
                case 1: menu_giao_dich(lib, role); break;
                case 2: 
                    read_input_string("  Nhập Mã bạn đọc cần xem: ", ma_bd);
                    lib.hien_thi_ma_muon_cua_bd(ma_bd);
                    break;
                case 3: 
                    read_input_string("  Nhập Mã bạn đọc cần đề xuất: ", ma_bd);
                    lib.de_xuat_tai_lieu(ma_bd);
                    break;
                case 0: return;
                default: cout << "Lựa chọn không hợp lệ." << endl;
            }
        }
    } while (choice != 0);
}


void menu_chinh(ThuVien& lib, UserRole& current_user_role, string& current_user_id) {
    int choice;
    string user, pass;

    do {
        cout << "\n========================================================" << endl;
        cout << "           HỆ THỐNG QUẢN LÝ THƯ VIỆN SỐ ĐẠI HỌC KINH TẾ QUỐC DÂN" << endl;
        cout << "================ MENU CHÍNH ================" << endl;
        cout << "1. Đăng nhập" << endl;
        cout << "2. Đăng ký tài khoản hệ thống (Admin/Thủ thư/Bạn đọc)" << endl;
        cout << "0. Thoát chương trình" << endl;
        cout << "Chọn chức năng: ";

        if (!(cin >> choice)) {
            cin.clear();
            choice = -1;
        }
        cin.ignore(10000, '\n');

        switch (choice) {
            case 1:
                read_input_string("  Nhập Username: ", user);
                read_input_string("  Nhập Password: ", pass);
                current_user_role = lib.login_user(user, pass);
                if (current_user_role != UserRole::UNKNOWN) {
                    current_user_id = user;
                    menu_chinh_chuc_nang(lib, current_user_role, current_user_id);
                    current_user_role = UserRole::UNKNOWN; 
                    current_user_id = "";
                }
                break;
            case 2:
                menu_dang_ky_he_thong(lib);
                break;
            case 0:
                cout << "\nCảm ơn bạn đã sử dụng hệ thống. Tạm biệt!" << endl;
                break;
            default:
                cout << "Lựa chọn không hợp lệ. Vui lòng thử lại." << endl;
        }
    } while (choice != 0);
}

int main() {
    cout << fixed << setprecision(0); 

    ThuVien myLibrary("Thư viện Số Tinh Giản");
    UserRole current_user_role = UserRole::UNKNOWN;
    string current_user_id = "";

    myLibrary.dang_ky_ban_doc("Nguyen Van A", "999111", "Ha Noi"); 
    myLibrary.them_tai_lieu("C++ Nâng Cao", "Tac Gia Mau", 2020, "Lap Trinh", "Sach In", "", ""); 
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
